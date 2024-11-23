#ifndef EXCLUSIVE_SYLLOGISM_H
#define EXCLUSIVE_SYLLOGISM_H

#include <memory>
#include "SyntaxTree.h"

class ExclusiveSyllogism {
public:
    static bool Apply(const std::shared_ptr<Node>& P, const std::shared_ptr<Node>& xorExpression, std::shared_ptr<Node>& result);

private:
    static bool IsXor(const std::shared_ptr<Node>& node);
};

#endif
