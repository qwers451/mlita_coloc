#include "Substitution.h"

std::shared_ptr<Node> Substitution::Apply(
    const std::shared_ptr<Node>& formula, 
    const std::unordered_map<std::string, std::shared_ptr<Node>>& substitutions) 
{
    if (!formula) {
        throw std::invalid_argument("Formula is null!");
    }
    return Substitute(formula, substitutions);
}

std::shared_ptr<Node> Substitution::Substitute(
    const std::shared_ptr<Node>& node, 
    const std::unordered_map<std::string, std::shared_ptr<Node>>& substitutions) 
{
    if (!node) return nullptr;

    if (node->type == NodeType::VARIABLE) {
        auto it = substitutions.find(node->value);
        if (it != substitutions.end()) {
            return it->second;
        }
        return node;
    }

    auto leftSubstituted = Substitute(node->left, substitutions);
    auto rightSubstituted = Substitute(node->right, substitutions);

    return std::make_shared<Node>(node->value, leftSubstituted, rightSubstituted);
}
