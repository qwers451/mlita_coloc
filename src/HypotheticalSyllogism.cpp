#include "HypotheticalSyllogism.h"

bool HypotheticalSyllogism::IsImplication(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == ">";
}

bool HypotheticalSyllogism::Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, std::shared_ptr<Node>& result) {
    if (!IsImplication(implication1) || !IsImplication(implication2)) return false;
    if (implication1->right && implication2->left && implication1->right->toString() == implication2->left->toString()) {
        result = std::make_shared<Node>(">", implication1->left, implication2->right);
        return true;
    }
    return false;
}
