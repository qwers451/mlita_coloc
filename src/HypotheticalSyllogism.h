#ifndef HYPOTHETICAL_SYLLOGISM_H
#define HYPOTHETICAL_SYLLOGISM_H

#include <memory>
#include "SyntaxTree.h"

class HypotheticalSyllogism {
public:
    static bool Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, std::shared_ptr<Node>& result);

private:
    static bool IsImplication(const std::shared_ptr<Node>& node);
};

#endif
