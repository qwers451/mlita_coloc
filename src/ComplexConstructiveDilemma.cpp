#include "ComplexConstructiveDilemma.h"

// Проверяет, является ли узел оператором импликации (">").
bool ComplexConstructiveDilemma::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

bool ComplexConstructiveDilemma::Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result) {
    if (!IsImplication(implication1) || !IsImplication(implication2) || !IsImplication(disjunction)) return false;

    if (disjunction->left && implication1->left && disjunction->left->left->toString() == implication1->left->toString() &&
        disjunction->right && implication2->left && disjunction->right->toString() == implication2->left->toString()) {
        result = std::make_shared<Node>("|", implication1->right, implication2->right);
        return true;
    }

    return false;
}
