#include "ExclusiveSyllogism.h"

bool ExclusiveSyllogism::IsXor(const std::shared_ptr<Node>& node) {
    return node && node->type == NodeType::OPERATOR && node->value == "xor";
}

bool ExclusiveSyllogism::Apply(const std::shared_ptr<Node>& P, const std::shared_ptr<Node>& xorExpression, std::shared_ptr<Node>& result) {
    if (!IsXor(xorExpression)) return false;
    if (xorExpression->left && xorExpression->right && xorExpression->left->toString() == P->toString()) {
        result = std::make_shared<Node>("!", xorExpression->right);
        return true;
    }
    return false;
}
