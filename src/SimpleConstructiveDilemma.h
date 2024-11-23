#ifndef SIMPLE_CONSTRUCTIVE_DILEMMA_H
#define SIMPLE_CONSTRUCTIVE_DILEMMA_H

#include <memory>
#include "SyntaxTree.h"

// Класс реализует правило простой конструктивной дилеммы: 
// Если P→R, Q→R и P∨Q, то можно вывести R.
class SimpleConstructiveDilemma {
public:
    // Проверяет возможность применения правила и вычисляет результат.
    // Вход:
    // - implication1: выражение P→R.
    // - implication2: выражение Q→R.
    // - disjunction: выражение P∨Q.
    // Выход:
    // - result: результат R, если правило применимо.
    static bool Apply(const std::shared_ptr<Node>& implication1, const std::shared_ptr<Node>& implication2, const std::shared_ptr<Node>& disjunction, std::shared_ptr<Node>& result);

private:
    // Проверяет, является ли узел импликацией.
    static bool IsImplication(const std::shared_ptr<Node>& node);

    // Проверяет, является ли узел дизъюнкцией.
    static bool IsDisjunction(const std::shared_ptr<Node>& node);
};

#endif
