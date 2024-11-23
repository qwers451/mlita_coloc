#ifndef SIMPLE_DESTRUCTIVE_DILEMMA_H
#define SIMPLE_DESTRUCTIVE_DILEMMA_H

#include <memory>
#include "SyntaxTree.h"

class SimpleDestructiveDilemma {
public:
    static bool Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result);

private:
    static bool IsImplication(const std::shared_ptr<Node>& node);
    static bool IsDisjunction(const std::shared_ptr<Node>& node);
};

#endif
