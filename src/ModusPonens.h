#ifndef MODUS_PONENS_H
#define MODUS_PONENS_H

#include <memory>
#include "SyntaxTree.h"

class ModusPonens {
public:
    // Проверяет, можно ли из A и A → B вывести B
    static bool Apply(const std::shared_ptr<Node>& A, const std::shared_ptr<Node>& implication, std::shared_ptr<Node>& result);

private:
    // Проверяет, является ли выражение импликацией
    static bool IsImplication(const std::shared_ptr<Node>& node);
};

#endif
