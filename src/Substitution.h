#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include "SyntaxTree.h"
#include <unordered_map>

class Substitution {
public:
    // Выполняет подстановку в корневом узле formula
    static std::shared_ptr<Node> Apply(
        const std::shared_ptr<Node>& formula, 
        const std::unordered_map<std::string, std::shared_ptr<Node>>& substitutions);

private:
    // Рекурсивная помощь в подстановке
    static std::shared_ptr<Node> Substitute(
        const std::shared_ptr<Node>& node, 
        const std::unordered_map<std::string, std::shared_ptr<Node>>& substitutions);
};

#endif
