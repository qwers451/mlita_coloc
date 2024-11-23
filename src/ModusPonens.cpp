#include "ModusPonens.h"

bool ModusPonens::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

// Реализация правила Modus Ponens
bool ModusPonens::Apply(const std::shared_ptr<Node>& A, const std::shared_ptr<Node>& implication, std::shared_ptr<Node>& result) {
    if (!IsImplication(implication)) return false;

    // Проверяем, что левая часть импликации равна A
    if (implication->left && A && implication->left->toString() == A->toString()) {
        result = implication->right;
        return true;
    }

    return false;
}
