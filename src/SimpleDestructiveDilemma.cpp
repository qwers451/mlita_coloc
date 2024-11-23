#include "SimpleDestructiveDilemma.h"

bool SimpleDestructiveDilemma::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

bool SimpleDestructiveDilemma::Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result) {
    if (!IsImplication(implication1) || !IsImplication(implication2) || !IsImplication(disjunction)) return false;

    if (disjunction->left && implication1->right && disjunction->left->left->left->toString() == implication1->right->toString() &&
        disjunction->right->left && implication2->right && disjunction->right->left->toString() == implication2->right->toString()) {
        result = std::make_shared<Node>("!", implication1->left);
        return true;
    }

    return false;
}
