#ifndef DISJUNCTIVE_SYLLOGISM_H
#define DISJUNCTIVE_SYLLOGISM_H

#include <memory>
#include "SyntaxTree.h"

class DisjunctiveSyllogism {
public:
    // Проверяет, можно ли из ⅂P и P ∨ Q вывести Q
    static bool Apply(const std::shared_ptr<Node>& notP, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result);

private:
    // Проверяет, является ли выражение дизъюнкцией
    static bool IsImplication(const std::shared_ptr<Node>& node);

    // Проверяет, является ли выражение отрицанием
    static bool IsNegation(const std::shared_ptr<Node>& node);
};

#endif
