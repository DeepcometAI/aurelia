#include "aurelia/token.hpp"
#include <stdexcept>
#include <cctype>
#include <sstream>

namespace aurelia {

std::unordered_map<std::string, TokenType> Lexer::keywords_ = {
    {"fn", TokenType::Fn},
    {"let", TokenType::Let},
    {"mut", TokenType::Mut},
    {"type", TokenType::Type},
    {"struct", TokenType::Struct},
    {"enum", TokenType::Enum},
    {"match", TokenType::Match},
    {"if", TokenType::If},
    {"else", TokenType::Else},
    {"for", TokenType::For},
    {"while", TokenType::While},
    {"return", TokenType::Return},
    {"async", TokenType::Async},
    {"await", TokenType::Await},
    {"parallel", TokenType::Parallel},
    {"tensor", TokenType::Tensor},
    {"dim", TokenType::Dim},
    {"true", TokenType::Bool},
    {"false", TokenType::Bool},
};

Lexer::Lexer(const std::string& source) : source_(source) {
    indentStack_.push_back(0);
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source_[current_];
}

char Lexer::advance() {
    char c = source_[current_++];
    column_++;
    return c;
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source_[current_] != expected) return false;
    current_++;
    column_++;
    return true;
}

bool Lexer::isAtEnd() const {
    return current_ >= source_.length();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r') {
            advance();
        } else if (c == '\n') {
            // Newlines are significant for indentation
            break;
        } else {
            break;
        }
    }
}

void Lexer::skipComment() {
    if (peek() == '#') {
        while (!isAtEnd() && peek() != '\n') {
            advance();
        }
    }
}

void Lexer::addToken(TokenType type) {
    addToken(type, std::monostate{});
}

void Lexer::addToken(TokenType type, std::variant<std::monostate, int64_t, double, std::string, bool> literal) {
    std::string text = source_.substr(start_, current_ - start_);
    tokens_.push_back(Token(type, literal.index() == 0 ? text : "", line_, column_));
    if (literal.index() != 0) {
        tokens_.back().literal = literal;
    }
}

void Lexer::number() {
    while (std::isdigit(peek())) advance();
    
    // Look for fractional part
    if (peek() == '.' && std::isdigit(source_[current_ + 1])) {
        advance(); // consume '.'
        while (std::isdigit(peek())) advance();
    }
    
    // Look for exponent
    if (peek() == 'e' || peek() == 'E') {
        advance();
        if (peek() == '+' || peek() == '-') advance();
        while (std::isdigit(peek())) advance();
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    if (text.find('.') != std::string::npos || text.find('e') != std::string::npos) {
        double value = std::stod(text);
        tokens_.push_back(Token(TokenType::Float, value, line_, column_));
    } else {
        int64_t value = std::stoll(text);
        tokens_.push_back(Token(TokenType::Integer, value, line_, column_));
    }
}

void Lexer::string() {
    advance(); // consume opening quote
    
    std::ostringstream ss;
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\\' && !isAtEnd()) {
            advance(); // consume backslash
            char escape = advance();
            switch (escape) {
                case 'n': ss << '\n'; break;
                case 't': ss << '\t'; break;
                case 'r': ss << '\r'; break;
                case '\\': ss << '\\'; break;
                case '"': ss << '"'; break;
                default: 
                    throw std::runtime_error("Invalid escape sequence");
            }
        } else {
            ss << advance();
        }
    }
    
    if (isAtEnd()) {
        throw std::runtime_error("Unterminated string");
    }
    
    advance(); // consume closing quote
    tokens_.push_back(Token(TokenType::String, ss.str(), line_, column_));
}

void Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();
    
    std::string text = source_.substr(start_, current_ - start_);
    auto it = keywords_.find(text);
    if (it != keywords_.end()) {
        tokens_.push_back(Token(it->second, text, line_, column_));
    } else {
        tokens_.push_back(Token(TokenType::Identifier, text, line_, column_));
    }
}

Token Lexer::nextToken() {
    skipWhitespace();
    skipComment();
    
    if (isAtEnd()) {
        return Token(TokenType::Eof, "", line_, column_);
    }
    
    start_ = current_;
    char c = advance();
    
    // Handle newlines and indentation
    if (c == '\n') {
        line_++;
        column_ = 1;
        
        // Calculate indentation of next line
        size_t indentStart = current_;
        int indent = 0;
        while (!isAtEnd() && (peek() == ' ' || peek() == '\t')) {
            if (peek() == ' ') indent++;
            else if (peek() == '\t') indent = (indent / 8 + 1) * 8;
            advance();
        }
        
        // Skip blank lines
        if (peek() == '\n' || peek() == '#' || isAtEnd()) {
            return nextToken();
        }
        
        // Generate Indent/Dedent tokens
        int prevIndent = indentStack_.back();
        if (indent > prevIndent) {
            indentStack_.push_back(indent);
            return Token(TokenType::Indent, "", line_, column_);
        } else if (indent < prevIndent) {
            while (indentStack_.size() > 1 && indentStack_.back() > indent) {
                indentStack_.pop_back();
                tokens_.push_back(Token(TokenType::Dedent, "", line_, column_));
            }
            if (!tokens_.empty()) {
                Token tok = tokens_.front();
                tokens_.erase(tokens_.begin());
                return tok;
            }
        }
        
        return Token(TokenType::Newline, "", line_, column_);
    }
    
    // Single-character tokens
    switch (c) {
        case '(': tokens_.push_back(Token(TokenType::LParen, "(", line_, column_)); break;
        case ')': tokens_.push_back(Token(TokenType::RParen, ")", line_, column_)); break;
        case '{': tokens_.push_back(Token(TokenType::LBrace, "{", line_, column_)); break;
        case '}': tokens_.push_back(Token(TokenType::RBrace, "}", line_, column_)); break;
        case '[': tokens_.push_back(Token(TokenType::LBracket, "[", line_, column_)); break;
        case ']': tokens_.push_back(Token(TokenType::RBracket, "]", line_, column_)); break;
        case ',': tokens_.push_back(Token(TokenType::Comma, ",", line_, column_)); break;
        case ':': tokens_.push_back(Token(TokenType::Colon, ":", line_, column_)); break;
        case ';': tokens_.push_back(Token(TokenType::Semicolon, ";", line_, column_)); break;
        case '.': tokens_.push_back(Token(TokenType::Dot, ".", line_, column_)); break;
        case '@': tokens_.push_back(Token(TokenType::At, "@", line_, column_)); break;
        case '+': tokens_.push_back(Token(TokenType::Plus, "+", line_, column_)); break;
        case '-': {
            if (match('>')) {
                tokens_.push_back(Token(TokenType::Arrow, "->", line_, column_));
            } else {
                tokens_.push_back(Token(TokenType::Minus, "-", line_, column_));
            }
            break;
        }
        case '*': tokens_.push_back(Token(TokenType::Star, "*", line_, column_)); break;
        case '/': tokens_.push_back(Token(TokenType::Slash, "/", line_, column_)); break;
        case '%': tokens_.push_back(Token(TokenType::Percent, "%", line_, column_)); break;
        case '^': tokens_.push_back(Token(TokenType::Caret, "^", line_, column_)); break;
        case '|': {
            if (match('>')) {
                tokens_.push_back(Token(TokenType::Pipe, "|>", line_, column_));
            } else {
                tokens_.push_back(Token(TokenType::Bang, "|", line_, column_));
            }
            break;
        }
        case '~': tokens_.push_back(Token(TokenType::Tilde, "~", line_, column_)); break;
        case '?': tokens_.push_back(Token(TokenType::Question, "?", line_, column_)); break;
        case '!': {
            if (match('=')) {
                tokens_.push_back(Token(TokenType::NotEqual, "!=", line_, column_));
            } else {
                tokens_.push_back(Token(TokenType::Bang, "!", line_, column_));
            }
            break;
        }
        case '=': {
            if (match('=')) {
                tokens_.push_back(Token(TokenType::EqualEqual, "==", line_, column_));
            } else {
                tokens_.push_back(Token(TokenType::Equal, "=", line_, column_));
            }
            break;
        }
        case '<': {
            if (match('=')) {
                tokens_.push_back(Token(TokenType::LessEqual, "<=", line_, column_));
            } else {
                tokens_.push_back(Token(TokenType::Less, "<", line_, column_));
            }
            break;
        }
        case '>': {
            if (match('=')) {
                tokens_.push_back(Token(TokenType::GreaterEqual, ">=", line_, column_));
            } else {
                tokens_.push_back(Token(TokenType::Greater, ">", line_, column_));
            }
            break;
        }
        case '"': string(); break;
        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c) || c == '_') {
                identifier();
            } else {
                throw std::runtime_error("Unexpected character: " + std::string(1, c));
            }
            break;
    }
    
    if (!tokens_.empty()) {
        Token tok = tokens_.front();
        tokens_.erase(tokens_.begin());
        return tok;
    }
    
    return nextToken();
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> result;
    while (!isAtEnd()) {
        Token tok = nextToken();
        if (tok.type != TokenType::Comment) {
            result.push_back(tok);
        }
        if (tok.type == TokenType::Eof) break;
    }
    return result;
}

} // namespace aurelia
