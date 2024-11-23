#ifndef THEOREM_PROVER_H
#define THEOREM_PROVER_H

#include "Axioms.h"
#include "ModusPonens.h"
#include "Substitution.h"
#include <unordered_set>
#include <queue>
#include <string>

class TheoremProver {
public:
    // Конструктор
    TheoremProver();

    // Пытается вывести заданное тождество
    bool Prove(const std::shared_ptr<Node>& target);

    // Возвращает список доказанных формул
    const std::unordered_set<std::string>& GetProvedFormulas() const;

private:
    // Хранит доказанные формулы (в виде строк)
    std::unordered_set<std::string> provedFormulas;

    // Очередь для обработки формул
    std::queue<std::shared_ptr<Node>> formulaQueue;

    // Добавляет новую формулу в доказанные и в очередь
    void AddFormula(const std::shared_ptr<Node>& formula);

    // Применяет подстановку к формуле
    std::shared_ptr<Node> ApplySubstitution(
        const std::shared_ptr<Node>& axiom,
        const std::unordered_map<std::string, std::shared_ptr<Node>>& substitution);

    // Пробует применить Modus Ponens к текущим доказанным формулам
    bool ApplyModusPonens(const std::shared_ptr<Node>& formula);
};

#endif
