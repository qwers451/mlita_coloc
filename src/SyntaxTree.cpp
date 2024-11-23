#include "SyntaxTree.h"

void Node::printTree(int indent)
{
    if (!this) return;

    std::string prefix(indent, ' ');

    std::cout << prefix;
    if (type == NodeType::VARIABLE) {
        std::cout << "Variable: " << value << "\n";
    } else if (type == NodeType::OPERATOR) {
        std::cout << "Operator: " << value << "\n";
    }

    if (left) {
        std::cout << prefix << " Left:\n";
        left->printTree(indent + 4);
    }

    if (right) {
        std::cout << prefix << " Right:\n";
        right->printTree(indent + 4);
    }
}

std::string Node::toString()
{
    if (!this) return "";

    if (type == NodeType::VARIABLE) {
        return value;
    }

    std::ostringstream result;

    if (value == "!") {
        result << value << left->toString();
    } else {
        result << "(" << left->toString() << " " << value << " " << right->toString() << ")";
    }

    return result.str();
}
