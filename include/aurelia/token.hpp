#pragma once

#include <string>
#include <variant>
#include <memory>
#include <unordered_map>
#include <vector>
#include <optional>
#include <cstdint>

namespace aurelia {

// Token types for the Aurelia lexer
enum class TokenType {
    // Literals
    Identifier,
    Integer,
    Float,
    String,
    Bool,
    
    // Keywords
    Fn,
    Let,
    Mut,
    Type,
    Struct,
    Enum,
    Match,
    If,
    Else,
    For,
    While,
    Return,
    Async,
    Await,
    Parallel,
    Tensor,
    Dim,
    
    // Operators
    Plus,
    Minus,
    Star,
    Slash,
    Percent,
    Caret,
    Arrow,
    Pipe,
    Tilde,
    Equal,
    EqualEqual,
    NotEqual,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    Question,
    Bang,
    
    // Delimiters
    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket,
    Comma,
    Colon,
    Semicolon,
    Dot,
    
    // Annotations
    At,
    
    // Special
    Indent,
    Dedent,
    Newline,
    Eof,
    Comment,
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::variant<std::monostate, int64_t, double, std::string, bool> literal;
    size_t line;
    size_t column;
    
    Token(TokenType t, const std::string& lex, size_t l = 0, size_t c = 0)
        : type(t), lexeme(lex), line(l), column(c) {}
    
    Token(TokenType t, int64_t val, size_t l = 0, size_t c = 0)
        : type(t), lexeme(std::to_string(val)), literal(val), line(l), column(c) {}
    
    Token(TokenType t, double val, size_t l = 0, size_t c = 0)
        : type(t), lexeme(std::to_string(val)), literal(val), line(l), column(c) {}
    
    Token(TokenType t, const std::string& val, size_t l = 0, size_t c = 0)
        : type(t), lexeme(val), literal(val), line(l), column(c) {}
    
    Token(TokenType t, bool val, size_t l = 0, size_t c = 0)
        : type(t), lexeme(val ? "true" : "false"), literal(val), line(l), column(c) {}
};

class Lexer {
public:
    explicit Lexer(const std::string& source);
    
    std::vector<Token> tokenize();
    Token nextToken();
    bool isAtEnd() const;
    
private:
    std::string source_;
    size_t start_ = 0;
    size_t current_ = 0;
    size_t line_ = 1;
    size_t column_ = 1;
    std::vector<int> indentStack_;
    
    char peek() const;
    char advance();
    bool match(char expected);
    void skipWhitespace();
    void skipComment();
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<std::monostate, int64_t, double, std::string, bool> literal);
    
    void number();
    void string();
    void identifier();
    
    static std::unordered_map<std::string, TokenType> keywords_;
};

} // namespace aurelia
