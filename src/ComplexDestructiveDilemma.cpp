#include "ComplexDestructiveDilemma.h"

bool ComplexDestructiveDilemma::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

bool ComplexDestructiveDilemma::Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result) {
    if (!IsImplication(implication1) || !IsImplication(implication2) || !IsImplication(disjunction)) return false;

    if (disjunction->left && implication1->right && disjunction->left->left->left->toString() == implication1->right->toString() &&
        disjunction->right->left && implication2->right && disjunction->right->left->toString() == implication2->right->toString()) {
        std::shared_ptr<Node> neg1 = std::make_shared<Node>("!", implication1->left);
        std::shared_ptr<Node> neg2 = std::make_shared<Node>("!", implication2->left);
        result = std::make_shared<Node>("|", neg1, neg2);
        return true;
    }

    return false;
}
