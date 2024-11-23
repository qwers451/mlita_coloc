#include "DisjunctiveSyllogism.h"

bool DisjunctiveSyllogism::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

// Проверяет, является ли узел отрицанием
bool DisjunctiveSyllogism::IsNegation(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == "!";
}

// Реализация правила Disjunctive Syllogism
bool DisjunctiveSyllogism::Apply(const std::shared_ptr<Node>& notP, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result) {
    if (!IsNegation(notP) || !IsImplication(disjunction)) return false;

    // Проверяем, что отрицание относится к одной из частей дизъюнкции
    if (notP->left && disjunction->left && notP->toString() == disjunction->left->toString()) {
        result = disjunction->right;
        return true;
    }

    return false;
}
