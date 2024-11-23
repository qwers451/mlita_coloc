#include "TheoremProver.h"

// Конструктор загружает начальные аксиомы
TheoremProver::TheoremProver() {
    auto axioms = Axioms::GetAxioms1To3();
    for (const auto& axiom : axioms) {
        AddFormula(axiom);
    }
}

// Добавляет формулу в доказанные и в очередь, если она еще не доказана
void TheoremProver::AddFormula(const std::shared_ptr<Node>& formula) {
    std::string formulaStr = formula->toString();
    if (provedFormulas.find(formulaStr) == provedFormulas.end()) {
        provedFormulas.insert(formulaStr);
        formulaQueue.push(formula);
    }
}

// Пробует вывести заданную формулу
bool TheoremProver::Prove(const std::shared_ptr<Node>& target) {
    std::string targetStr = target->toString();

    // Проверяем, доказана ли формула
    if (provedFormulas.find(targetStr) != provedFormulas.end()) {
        return true;
    }

    // Пока есть формулы для обработки
    while (!formulaQueue.empty()) {
        auto current = formulaQueue.front();
        formulaQueue.pop();

        // Пробуем применить Modus Ponens
        if (ApplyModusPonens(current)) {
            if (provedFormulas.find(targetStr) != provedFormulas.end()) {
                return true;
            }
        }

        // Применяем подстановки аксиом
        auto axioms = Axioms::GetAxioms1To3();
        for (const auto& axiom : axioms) {
            // Пример подстановки для текущей формулы
            std::unordered_map<std::string, std::shared_ptr<Node>> substitution = {
                {"A", current},
                {"B", current->left},
                {"C", current->right}
            };

            auto substituted = ApplySubstitution(axiom, substitution);
            if (substituted) {
                AddFormula(substituted);
            }
        }

        std::queue<std::shared_ptr<Node>> q_copy = formulaQueue;
        while (!q_copy.empty())
        {
            auto front = q_copy.front();
            std::cout << front->toString() << '\n';
            q_copy.pop();
        }
        std::string fl;
        std::cin >> fl;
    }

    return false;
}

// Применяет Modus Ponens к доказанным формулам
bool TheoremProver::ApplyModusPonens(const std::shared_ptr<Node>& formula) {
    for (const auto& provedStr : provedFormulas) {
        auto provedFormula = FormulaParser::Parse(provedStr);

        std::shared_ptr<Node> result;
        if (ModusPonens::Apply(provedFormula, formula, result) ||
            ModusPonens::Apply(formula, provedFormula, result)) {
            AddFormula(result);
        }
    }
    return false;
}

// Применяет подстановку к формуле
std::shared_ptr<Node> TheoremProver::ApplySubstitution(
    const std::shared_ptr<Node>& axiom,
    const std::unordered_map<std::string, std::shared_ptr<Node>>& substitution) {
    return Substitution::Apply(axiom, substitution);
}

// Возвращает список доказанных формул
const std::unordered_set<std::string>& TheoremProver::GetProvedFormulas() const {
    return provedFormulas;
}
