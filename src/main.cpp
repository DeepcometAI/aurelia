#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Forward declarations for lexer and parser
namespace aurelia {
    struct Module;
    Module parse(const std::string& source);
}

void printUsage(const char* program) {
    std::cout << "Aurelia Compiler v0.1.0-alpha\n";
    std::cout << "Usage: " << program << " [options] <input.aul>\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help     Show this help message\n";
    std::cout << "  -v, --version  Show version information\n";
    std::cout << "  -o <file>      Output file (default: a.out)\n";
    std::cout << "  --emit-ast     Print AST and exit\n";
    std::cout << "  --emit-tokens  Print tokens and exit\n";
    std::cout << "  -O0            No optimization (debug)\n";
    std::cout << "  -O3            Maximum optimization (release)\n";
    std::cout << "\nExamples:\n";
    std::cout << "  " << program << " hello.aul -o hello\n";
    std::cout << "  " << program << " --emit-ast program.aul\n";
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string inputFile;
    std::string outputFile = "a.out";
    bool emitAst = false;
    bool emitTokens = false;
    std::string optimizationLevel = "O0";
    
    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            std::cout << "Aurelia Compiler v0.1.0-alpha\n";
            std::cout << "Built with C++23\n";
            return 0;
        } else if (arg == "-o") {
            if (i + 1 >= argc) {
                std::cerr << "Error: -o requires an argument\n";
                return 1;
            }
            outputFile = argv[++i];
        } else if (arg == "--emit-ast") {
            emitAst = true;
        } else if (arg == "--emit-tokens") {
            emitTokens = true;
        } else if (arg == "-O0" || arg == "-O3") {
            optimizationLevel = arg.substr(1);
        } else if (arg[0] != '-') {
            inputFile = arg;
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }
    
    if (inputFile.empty()) {
        std::cerr << "Error: No input file specified\n";
        printUsage(argv[0]);
        return 1;
    }
    
    try {
        // Read source file
        std::string source = readFile(inputFile);
        
        std::cout << "Compiling " << inputFile << "...\n";
        
        // Parse the source
        aurelia::Module module = aurelia::parse(source);
        
        std::cout << "Successfully parsed " << module.statements.size() << " statements\n";
        
        if (emitAst) {
            std::cout << "AST emission not yet implemented\n";
        }
        
        if (emitTokens) {
            std::cout << "Token emission not yet implemented\n";
        }
        
        // TODO: Continue with type checking, IR generation, optimization, codegen
        
        std::cout << "Compilation complete (frontend only)\n";
        std::cout << "Note: Backend codegen is not yet implemented in this alpha version\n";
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
