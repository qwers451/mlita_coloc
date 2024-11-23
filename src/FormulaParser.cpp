#include "FormulaParser.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

bool IsValidVariable(const std::string& input) {
    return input.size() == 1 && std::isalpha(input[0]);
}

void SkipSpaces(const std::string& input, size_t& pos) {
    while (pos < input.size() && std::isspace(input[pos])) {
        pos++;
    }
}

std::shared_ptr<Node> FormulaParser::Parse(const std::string& input) {
    size_t pos = 0;
    auto result = ParseExpression(input, pos, 0);

    SkipSpaces(input, pos);
    if (pos != input.size()) {
        throw std::invalid_argument("Parsing error: the input contains invalid characters!");
    }

    return result;
}

std::shared_ptr<Node> FormulaParser::ParseExpression(const std::string& input, size_t& pos, int precedence) {
    SkipSpaces(input, pos);
    auto left = ParsePrimary(input, pos);

    while (pos < input.size()) {
        SkipSpaces(input, pos);

        char op = input[pos];
        int currentPrecedence = GetPrecedence(op);
        if (currentPrecedence < precedence) break;

        pos++;
        auto right = ParseExpression(input, pos, currentPrecedence + 1);

        if (op == '*') {
            // A * B => !(A > !B)
            auto notB = std::make_shared<Node>("!", right);
            auto implication = std::make_shared<Node>(">", left, notB);
            left = std::make_shared<Node>("!", implication);
        } else if (op == '|') {
            // A | B => (!A > B)
            auto notA = std::make_shared<Node>("!", left);
            left = std::make_shared<Node>(">", notA, right);
        } else {
            left = std::make_shared<Node>(std::string(1, op), left, right);
        }
    }

    return left;
}

std::shared_ptr<Node> FormulaParser::ParsePrimary(const std::string& input, size_t& pos) {
    SkipSpaces(input, pos);

    if (pos >= input.size()) throw std::invalid_argument("Parsing error: unexpected end of input!");

    if (input[pos] == '(') {
        pos++;
        auto expr = ParseExpression(input, pos, 0);
        SkipSpaces(input, pos);

        if (pos >= input.size() || input[pos] != ')') {
            std::string a = "Parsing error: missing closing parenthesis!: Pos: " + std::string(1, pos) + " in expression: " + input;
            throw std::invalid_argument(a);
        }
        pos++;
        return expr;
    }

    if (input[pos] == '!') {
        pos++;
        auto operand = ParsePrimary(input, pos);
        return std::make_shared<Node>("!", operand);
    }

    if (std::isalpha(input[pos])) {
        std::string variable(1, input[pos++]);
        if (!IsValidVariable(variable)) {
            throw std::invalid_argument("Parsing error: invalid variable '" + variable + "'!");
        }
        return std::make_shared<Node>(variable);
    }

    throw std::invalid_argument("Parsing error: invalid character!");
}

int FormulaParser::GetPrecedence(char op) {
    switch (op) {
        case '!': return 3;
        case '*': return 2;
        case '|': return 1;
        case '>': return 0;
        default:  return -1;
    }
}
