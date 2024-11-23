#ifndef MODUS_TOLLENS_H
#define MODUS_TOLLENS_H

#include <memory>
#include "SyntaxTree.h"

class ModusTollens {
public:
    static bool Apply(const std::shared_ptr<Node>& implication, const std::shared_ptr<Node>& notQ, std::shared_ptr<Node>& result);

private:
    static bool IsNegation(const std::shared_ptr<Node>& node);
    static bool IsImplication(const std::shared_ptr<Node>& node);
};

#endif
