#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include "SyntaxTree.h"

class FormulaParser {
public:
    // Парсит строку с формулой и возвращает корень синтаксического дерева
    static std::shared_ptr<Node> Parse(const std::string& input);

private:
    // Рекурсивно парсит выражение, учитывая приоритет операторов
    static std::shared_ptr<Node> ParseExpression(const std::string& input, size_t& pos, int precedence);

    // Парсит базовые элементы формулы, такие как переменные, скобки или операторы отрицания
    static std::shared_ptr<Node> ParsePrimary(const std::string& input, size_t& pos);

    // Возвращает приоритет указанного оператора
    static int GetPrecedence(char op);
};

#endif
