#include "ModusTollens.h"

// Проверяет, является ли узел отрицанием
bool ModusTollens::IsNegation(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == "!";
}

// Проверяет, является ли узел импликацией
bool ModusTollens::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

// Реализация правила Modus Tollens
bool ModusTollens::Apply(const std::shared_ptr<Node>& implication, const std::shared_ptr<Node>& notQ, std::shared_ptr<Node>& result) {
    // Проверяем, что первое выражение является импликацией
    if (!IsImplication(implication)) return false;

    // Проверяем, что второе выражение является отрицанием
    if (!IsNegation(notQ)) return false;

    // Проверяем, что отрицание относится к правой части импликации
    if (notQ->left && implication->right && notQ->left->toString() == implication->right->toString()) {
        // Формируем результат: ⅂P
        result = std::make_shared<Node>("!", implication->left);
        return true;
    }

    return false;
}
