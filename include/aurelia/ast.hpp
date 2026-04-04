#pragma once

#include "aurelia/token.hpp"
#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <optional>

namespace aurelia {

// Forward declarations
struct Expression;
struct Statement;

using ExprPtr = std::shared_ptr<Expression>;
using StmtPtr = std::shared_ptr<Statement>;

// Expression types
struct IntegerLiteral {
    int64_t value;
};

struct FloatLiteral {
    double value;
};

struct StringLiteral {
    std::string value;
};

struct BoolLiteral {
    bool value;
};

struct Identifier {
    std::string name;
};

struct BinaryOp {
    ExprPtr left;
    std::string op;
    ExprPtr right;
};

struct UnaryOp {
    std::string op;
    ExprPtr operand;
};

struct Call {
    ExprPtr callee;
    std::vector<ExprPtr> arguments;
};

struct Index {
    ExprPtr target;
    ExprPtr index;
};

struct Slice {
    ExprPtr target;
    std::optional<ExprPtr> start;
    std::optional<ExprPtr> end;
};

struct TensorLiteral {
    std::vector<ExprPtr> elements;
    std::vector<size_t> shape;
};

struct Pipe {
    ExprPtr left;
    ExprPtr right;  // Call expression
};

struct Formula {
    ExprPtr left;
    ExprPtr right;  // Right side of ~ operator
};

struct Match {
    ExprPtr subject;
    struct Arm {
        ExprPtr pattern;
        ExprPtr body;
    };
    std::vector<Arm> arms;
};

struct Lambda {
    std::vector<std::string> params;
    ExprPtr body;
};

struct TypeAnnotation {
    std::string type_name;
    std::vector<ExprPtr> type_params;
};

struct TypedExpr {
    ExprPtr expr;
    TypeAnnotation type;
};

// Statement types
struct LetStmt {
    std::string name;
    std::optional<TypeAnnotation> type;
    ExprPtr init;
};

struct MutStmt {
    std::string name;
    std::optional<TypeAnnotation> type;
    std::optional<ExprPtr> init;
};

struct FnDef {
    std::string name;
    std::vector<std::pair<std::string, TypeAnnotation>> params;
    std::optional<TypeAnnotation> return_type;
    std::vector<StmtPtr> body;
    std::vector<std::string> decorators;
};

struct TypeDef {
    std::string name;
    ExprPtr definition;
};

struct StructDef {
    std::string name;
    std::vector<std::pair<std::string, TypeAnnotation>> fields;
};

struct IfStmt {
    ExprPtr condition;
    std::vector<StmtPtr> then_branch;
    std::optional<std::vector<StmtPtr>> else_branch;
};

struct ForStmt {
    std::string var;
    ExprPtr iterable;
    std::vector<StmtPtr> body;
    bool is_parallel = false;
};

struct WhileStmt {
    ExprPtr condition;
    std::vector<StmtPtr> body;
};

struct ReturnStmt {
    std::optional<ExprPtr> value;
};

struct ExprStmt {
    ExprPtr expr;
};

struct Block {
    std::vector<StmtPtr> statements;
};

struct AsyncBlock {
    std::vector<StmtPtr> body;
};

struct Annotation {
    std::string name;
    std::vector<std::pair<std::string, ExprPtr>> args;
};

// Variant types
struct Expression {
    std::variant<
        IntegerLiteral,
        FloatLiteral,
        StringLiteral,
        BoolLiteral,
        Identifier,
        BinaryOp,
        UnaryOp,
        Call,
        Index,
        Slice,
        TensorLiteral,
        Pipe,
        Formula,
        Match,
        Lambda,
        TypedExpr
    > data;
};

struct Statement {
    std::variant<
        LetStmt,
        MutStmt,
        FnDef,
        TypeDef,
        StructDef,
        IfStmt,
        ForStmt,
        WhileStmt,
        ReturnStmt,
        ExprStmt,
        Block,
        AsyncBlock,
        Annotation
    > data;
};

// AST Node wrapper
struct AstNode {
    std::variant<ExprPtr, StmtPtr> node;
    
    template<typename T>
    bool is() const {
        return std::holds_alternative<T>(node);
    }
    
    template<typename T>
    T& as() {
        return std::get<T>(node);
    }
};

// Module (top-level AST)
struct Module {
    std::string name;
    std::vector<StmtPtr> statements;
    std::vector<Annotation> annotations;
};

} // namespace aurelia
