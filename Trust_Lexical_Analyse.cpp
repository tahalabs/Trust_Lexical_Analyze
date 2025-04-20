#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <map>
#include <memory>

enum TokenType {
    // Keywords
    T_Bool, T_Break, T_Continue, T_Else, T_False, T_Fn, T_Int, T_If, T_Let,
    T_Loop, T_Mut, T_Print, T_Return, T_True,

    // Arithmetic Operators
    T_AOp_Trust, T_AOp_MN, T_AOp_ML, T_AOp_DV, T_AOp_RM,

    // Relational Operators
    T_ROp_L, T_ROp_G, T_ROp_LE, T_ROp_GE, T_ROp_NE, T_ROp_E,

    // Logical Operators
    T_LOp_AND, T_LOp_OR, T_LOp_NOT,

    // Assignment
    T_Assign,

    // Symbols
    T_LP, T_RP, T_LC, T_RC, T_LB, T_RB,
    T_Semicolon, T_Comma, T_Colon, T_Arrow,

    // Identifiers and literals
    T_Id, T_Decimal, T_Hexadecimal, T_String,

    // Comments and Whitespace
    T_Comment, T_Whitespace,

    T_Unknown
};

std::map<std::string, TokenType> keywords = {
    {"bool", T_Bool}, {"break", T_Break}, {"continue", T_Continue}, {"else", T_Else},
    {"false", T_False}, {"fn", T_Fn}, {"i32", T_Int}, {"if", T_If},
    {"let", T_Let}, {"loop", T_Loop}, {"mut", T_Mut}, {"println!", T_Print},
    {"return", T_Return}, {"true", T_True}
};

struct Token {
    TokenType type;
    std::string value;
};

struct ASTNode {
    std::string name;
    std::vector<std::shared_ptr<ASTNode>> children;
};

class SemanticAnalyzer {
    std::vector<std::string> symbolTable;
public:
    void analyze(std::shared_ptr<ASTNode> node) {
        if (!node) return;

        if (node->name == "let_declaration") {
            std::string varName = node->children[1]->name;
            if (isDeclared(varName)) {
                std::cerr << "خطا: متغیر " << varName << " قبلا تعریف شده است!\n";
            } else {
                symbolTable.push_back(varName);
            }
        }

        if (node->name == "identifier") {
            std::string varName = node->children[0]->name;
            if (!isDeclared(varName)) {
                std::cerr << "خطا: متغیر " << varName << " تعریف نشده است!\n";
            }
        }

        for (auto& child : node->children) {
            analyze(child);
        }
    }

    bool isDeclared(const std::string& name) {
        return std::find(symbolTable.begin(), symbolTable.end(), name) != symbolTable.end();
    }
};

// اضافه کردن تابع getSymbolToken
TokenType getSymbolToken(const std::string& lexeme) {
    if (lexeme == "=") return T_Assign;
    if (lexeme == "+") return T_AOp_Trust;
    if (lexeme == "-") return T_AOp_MN;
    if (lexeme == "*") return T_AOp_ML;
    if (lexeme == "/") return T_AOp_DV;
    if (lexeme == "%") return T_AOp_RM;
    if (lexeme == "<") return T_ROp_L;
    if (lexeme == ">") return T_ROp_G;
    if (lexeme == "<=") return T_ROp_LE;
    if (lexeme == ">=") return T_ROp_GE;
    if (lexeme == "!=") return T_ROp_NE;
    if (lexeme == "==") return T_ROp_E;
    if (lexeme == "&&") return T_LOp_AND;
    if (lexeme == "||") return T_LOp_OR;
    if (lexeme == "!") return T_LOp_NOT;
    if (lexeme == "(") return T_LP;
    if (lexeme == ")") return T_RP;
    if (lexeme == "{") return T_LC;
    if (lexeme == "}") return T_RC;
    if (lexeme == "[") return T_LB;
    if (lexeme == "]") return T_RB;
    if (lexeme == ";") return T_Semicolon;
    if (lexeme == ",") return T_Comma;
    if (lexeme == ":") return T_Colon;
    if (lexeme == "->") return T_Arrow;
    
    return T_Unknown; // اگر نماد شناخته نشده باشد
}

// اضافه کردن تابع tokenTypeToString
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case T_Bool: return "T_Bool";
        case T_Break: return "T_Break";
        case T_Continue: return "T_Continue";
        case T_Else: return "T_Else";
        case T_False: return "T_False";
        case T_Fn: return "T_Fn";
        case T_Int: return "T_Int";
        case T_If: return "T_If";
        case T_Let: return "T_Let";
        case T_Loop: return "T_Loop";
        case T_Mut: return "T_Mut";
        case T_Print: return "T_Print";
        case T_Return: return "T_Return";
        case T_True: return "T_True";

        case T_AOp_Trust: return "T_AOp_Trust";
        case T_AOp_MN: return "T_AOp_MN";
        case T_AOp_ML: return "T_AOp_ML";
        case T_AOp_DV: return "T_AOp_DV";
        case T_AOp_RM: return "T_AOp_RM";

        case T_ROp_L: return "T_ROp_L";
        case T_ROp_G: return "T_ROp_G";
        case T_ROp_LE: return "T_ROp_LE";
        case T_ROp_GE: return "T_ROp_GE";
        case T_ROp_NE: return "T_ROp_NE";
        case T_ROp_E: return "T_ROp_E";

        case T_LOp_AND: return "T_LOp_AND";
        case T_LOp_OR: return "T_LOp_OR";
        case T_LOp_NOT: return "T_LOp_NOT";

        case T_Assign: return "T_Assign";
        case T_LP: return "T_LP";
        case T_RP: return "T_RP";
        case T_LC: return "T_LC";
        case T_RC: return "T_RC";
        case T_LB: return "T_LB";
        case T_RB: return "T_RB";
        case T_Semicolon: return "T_Semicolon";
        case T_Comma: return "T_Comma";
        case T_Colon: return "T_Colon";
        case T_Arrow: return "T_Arrow";

        case T_Id: return "T_Id";
        case T_Decimal: return "T_Decimal";
        case T_Hexadecimal: return "T_Hexadecimal";
        case T_String: return "T_String";

        case T_Comment: return "T_Comment";
        case T_Whitespace: return "T_Whitespace";
        case T_Unknown: return "T_Unknown";

        default: return "Unknown";
    }
}

bool isKeyword(const std::string& word) {
    return keywords.find(word) != keywords.end();
}

std::vector<Token> tokenize(const std::string& code) {
    std::vector<Token> tokens;

    std::regex tokenRegex(R"((\/\/[^\n]*\n)|("(\\.|[^"])*")|0x[0-9a-fA-F]+|[0-9]+|->|!=|==|<=|>=|&&|\|\||[a-zA-Z_][a-zA-Z0-9_]*|[-+*/%=<>{}()[\];,:!]|[ \t\n])");
    auto wordsBegin = std::sregex_iterator(code.begin(), code.end(), tokenRegex);
    auto wordsEnd = std::sregex_iterator();

    for (auto it = wordsBegin; it != wordsEnd; ++it) {
        std::string lexeme = it->str();

        if (std::regex_match(lexeme, std::regex(R"([ \t\n])"))) {
            tokens.push_back({T_Whitespace, lexeme});
        } else if (std::regex_match(lexeme, std::regex(R"(\/\/[^\n]*\n)"))) {
            tokens.push_back({T_Comment, lexeme});
        } else if (isKeyword(lexeme)) {
            tokens.push_back({keywords[lexeme], lexeme});
        } else if (std::regex_match(lexeme, std::regex(R"([a-zA-Z_][a-zA-Z0-9_]*)"))) {
            tokens.push_back({T_Id, lexeme});
        } else if (std::regex_match(lexeme, std::regex(R"(0x[0-9a-fA-F]+)"))) {
            tokens.push_back({T_Hexadecimal, lexeme});
        } else if (std::regex_match(lexeme, std::regex(R"([0-9]+)"))) {
            tokens.push_back({T_Decimal, lexeme});
        } else if (std::regex_match(lexeme, std::regex(R"("(\\.|[^"])*")"))) {
            tokens.push_back({T_String, lexeme});
        } else {
            TokenType type = getSymbolToken(lexeme);
            if (type != T_Unknown)
                tokens.push_back({type, lexeme});
            else
                tokens.push_back({T_Unknown, lexeme});
        }
    }

    return tokens;
}

int main() {
    std::ifstream input("test.trust");
    if (!input) {
        std::cerr << "خطا در باز کردن فایل ورودی.\n";
        return 1;
    }

    std::string code((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    std::vector<Token> tokens = tokenize(code);

    std::cout << "Tokens:\n";
    for (const auto& token : tokens) {
        if (token.type != T_Whitespace && token.type != T_Comment)
            std::cout << tokenTypeToString(token.type) << ": " << token.value << '\n';
    }

    // فرض کنیم ast از parser ساخته شده
    std::shared_ptr<ASTNode> ast = std::make_shared<ASTNode>();
    SemanticAnalyzer analyzer;
    analyzer.analyze(ast);

    return 0;
}
