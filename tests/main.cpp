#include <iostream>
#include "../src/FormulaParser.h"
#include "../src/Substitution.h"
#include "../src/ModusPonens.h"
#include "../src/ModusTollens.h"
#include "../src/DisjunctiveSyllogism.h"
#include "../src/HypotheticalSyllogism.h"
#include "../src/SimpleConstructiveDilemma.h"
#include "../src/ComplexConstructiveDilemma.h"
#include "../src/SimpleDestructiveDilemma.h"
#include "../src/ComplexDestructiveDilemma.h"

void TestFormulaParser() {
    try {
        std::cout << "\nTestFormulaParser:\n";
        // Test 1: Простое выражение
        auto formula1 = FormulaParser::Parse("A > B");
        std::cout << "Test 1: Expected: (A > B)   Got: " << formula1->toString() << "\n";

        // Test 2: Унарный оператор
        auto formula2 = FormulaParser::Parse("!(A > B)");
        std::cout << "Test 2: Expected: !(A > B)   Got: " << formula2->toString() << "\n"; // Ожидается: !(A > B)

        // Test 3: Скобки и приоритет
        auto formula3 = FormulaParser::Parse("(A > B) > C");
        std::cout << "Test 3: Expected: ((A > B) > C)   Got: " << formula3->toString() << "\n";

        // Test 4: Смешанные операторы
        auto formula4 = FormulaParser::Parse("(A>(B>(A*B)))");
        std::cout << "Test 4: Expected: (A > (B > !(A > !B)))   Got: " << formula4->toString() << "\n";

        // Test 5: Неверный ввод
        try {
            auto formula5 = FormulaParser::Parse("A > B)");
        } catch (const std::exception& ex) {
            std::cout << "Test 5: Expected: ERROR   Got: Caught error: " << ex.what() << "\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "FormulaParser Test Error: " << ex.what() << "\n";
    }
}

void TestSubstitution() {
    try {
        std::cout << "\nTestSubstitution:\n";
        // Test 1: Простая подстановка
        auto formula1 = FormulaParser::Parse("A > B");
        std::unordered_map<std::string, std::shared_ptr<Node>> subs1 = {
            {"A", FormulaParser::Parse("X")},
            {"B", FormulaParser::Parse("Y")}
        };
        auto result1 = Substitution::Apply(formula1, subs1);
        std::cout << "Test 1: Expected: (X > Y)   Got: " << result1->toString() << "\n";

        // Test 2: Замена на сложное выражение
        auto formula2 = FormulaParser::Parse("A > (B > C)");
        std::unordered_map<std::string, std::shared_ptr<Node>> subs2 = {
            {"A", FormulaParser::Parse("(P * Q)")},
            {"B", FormulaParser::Parse("!R")},
            {"C", FormulaParser::Parse("(S > T)")}
        };
        auto result2 = Substitution::Apply(formula2, subs2);
        std::cout << "Test 2: Expected: (!(P > !Q) > (!R > (S > T)))   Got: " << result2->toString() << "\n";

        // Test 3: Частичная подстановка
        auto formula3 = FormulaParser::Parse("A > B");
        std::unordered_map<std::string, std::shared_ptr<Node>> subs3 = {
            {"A", FormulaParser::Parse("X")}
        };
        auto result3 = Substitution::Apply(formula3, subs3);
        std::cout << "Test 3: Expected: (X > B)   Got: " << result3->toString() << "\n";

        // Test 4: Подстановка с оператором отрицания
        auto formula4 = FormulaParser::Parse("!A");
        std::unordered_map<std::string, std::shared_ptr<Node>> subs4 = {
            {"A", FormulaParser::Parse("(P > Q)")}
        };
        auto result4 = Substitution::Apply(formula4, subs4);
        std::cout << "Test 4: Expected: !(P > Q)   Got: " << result4->toString() << "\n";

        // Test 5: Нет замены
        auto formula5 = FormulaParser::Parse("A > B");
        std::unordered_map<std::string, std::shared_ptr<Node>> subs5; // Пустой словарь
        auto result5 = Substitution::Apply(formula5, subs5);
        std::cout << "Test 5: Expected: (A > B)   Got: " << result5->toString() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Substitution Test Error: " << ex.what() << "\n";
    }
}

void TestModusPonens() {
    try {
        std::cout << "\nTestModusPonens:\n";
        // Test 1: Простой случай
        auto A = FormulaParser::Parse("P");
        auto implication1 = FormulaParser::Parse("P > Q");
        std::shared_ptr<Node> result1;
        if (ModusPonens::Apply(A, implication1, result1)) {
            std::cout << "Test 1: Expected: Q   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }

        // Test 2: Сложное А
        auto A2 = FormulaParser::Parse("(P * Q)");
        auto implication2 = FormulaParser::Parse("(P * Q) > (R > S)");
        std::shared_ptr<Node> result2;
        if (ModusPonens::Apply(A2, implication2, result2)) {
            std::cout << "Test 2: Expected: (R > S)   Got: " << result2->toString() << "\n";
        } else {
            std::cout << "Test 2 failed\n";
        }

        // Test 3: Несовпадение (A не является антецедентом)
        auto A3 = FormulaParser::Parse("P");
        auto implication3 = FormulaParser::Parse("Q > R");
        std::shared_ptr<Node> result3;
        if (!ModusPonens::Apply(A3, implication3, result3)) {
            std::cout << "Test 3 passed: No valid result\n";
        } else {
            std::cout << "Test 3 failed: Incorrectly returned " << result3->toString() << "\n";
        }

        // Test 4: Вложенная импликация
        auto A4 = FormulaParser::Parse("P");
        auto implication4 = FormulaParser::Parse("P > (Q > R)");
        std::shared_ptr<Node> result4;
        if (ModusPonens::Apply(A4, implication4, result4)) {
            std::cout << "Test 4: Expected: (Q > R)   Got: " << result4->toString() << "\n";
        } else {
            std::cout << "Test 4 failed\n";
        }

        // Test 5: Импликация со сложным результатом
        auto A5 = FormulaParser::Parse("!P");
        auto implication5 = FormulaParser::Parse("!P > (Q * R)");
        std::shared_ptr<Node> result5;
        if (ModusPonens::Apply(A5, implication5, result5)) {
            std::cout << "Test 5: Expected: !(Q > !R)   Got: " << result5->toString() << "\n";
        } else {
            std::cout << "Test 5 failed\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "ModusPonens Test Error: " << ex.what() << "\n";
    }
}

void TestModusTollens() {
    try {
        std::cout << "\nTestModusTollens:\n";
        // Test 1: Простой случай
        auto implication1 = FormulaParser::Parse("P > Q");
        auto notQ = FormulaParser::Parse("!Q");
        std::shared_ptr<Node> result1;
        if (ModusTollens::Apply(implication1, notQ, result1)) {
            std::cout << "Test 1: Expected: !P   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "ModusTollens Test Error: " << ex.what() << "\n";
    }
}

void TestDisjunctiveSyllogism() {
    try {
        std::cout << "\nTestDisjunctiveSyllogism:\n";
        // Test 1: Простой случай
        auto disjunction = FormulaParser::Parse("P | Q");
        auto notP = FormulaParser::Parse("!P");
        std::shared_ptr<Node> result1;
        if (DisjunctiveSyllogism::Apply(notP, disjunction, result1)) {
            std::cout << "Test 1: Expected: Q   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "DisjunctiveSyllogism Test Error: " << ex.what() << "\n";
    }
}

void TestHypotheticalSyllogism() {
    try {
        std::cout << "\nTestHypotheticalSyllogism:\n";
        
        auto premise1 = FormulaParser::Parse("P > Q");
        auto premise2 = FormulaParser::Parse("Q > R");
        std::shared_ptr<Node> result1;
        if (HypotheticalSyllogism::Apply(premise1, premise2, result1)) {
            std::cout << "Test 1: Expected: P > R   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "HypotheticalSyllogism Test Error: " << ex.what() << "\n";
    }
}

void TestSimpleConstructiveDilemma() {
    try {
        std::cout << "\nTestSimpleConstructiveDilemma:\n";
        
        auto premise1 = FormulaParser::Parse("P > R");
        auto premise2 = FormulaParser::Parse("Q > R");
        auto disjunction = FormulaParser::Parse("P | Q");
        std::shared_ptr<Node> result1;
        if (SimpleConstructiveDilemma::Apply(premise1, premise2, disjunction, result1)) {
            std::cout << "Test 1: Expected: (R)   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "SimpleConstructiveDilemma Test Error: " << ex.what() << "\n";
    }
}

void TestComplexConstructiveDilemma() {
    try {
        std::cout << "\nTestComplexConstructiveDilemma:\n";
        
        auto premise1 = FormulaParser::Parse("P > R");
        auto premise2 = FormulaParser::Parse("Q > T");
        auto disjunction = FormulaParser::Parse("P | Q");
        std::shared_ptr<Node> result1;
        if (ComplexConstructiveDilemma::Apply(premise1, premise2, disjunction, result1)) {
            std::cout << "Test 1: Expected: (R | T)   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "ComplexConstructiveDilemma Test Error: " << ex.what() << "\n";
    }
}

void TestSimpleDestructiveDilemma() {
    try {
        std::cout << "\nTestSimpleDestructiveDilemma:\n";
        
        auto premise1 = FormulaParser::Parse("P > Q");
        auto premise2 = FormulaParser::Parse("R > S");
        auto disjunction = FormulaParser::Parse("!Q | !S");
        std::shared_ptr<Node> result1;
        if (SimpleDestructiveDilemma::Apply(premise1, premise2, disjunction, result1)) {
            std::cout << "Test 1: Expected: !P   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "SimpleDestructiveDilemma Test Error: " << ex.what() << "\n";
    }
}

void TestComplexDestructiveDilemma() {
    try {
        std::cout << "\nTestComplexDestructiveDilemma:\n";
        
        auto premise1 = FormulaParser::Parse("P > R");
        auto premise2 = FormulaParser::Parse("Q > T");
        auto disjunction = FormulaParser::Parse("!R | !T");
        std::shared_ptr<Node> result1;
        if (ComplexDestructiveDilemma::Apply(premise1, premise2, disjunction, result1)) {
            std::cout << "Test 1: Expected: (!P | !Q)   Got: " << result1->toString() << "\n";
        } else {
            std::cout << "Test 1 failed\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "ComplexDestructiveDilemma Test Error: " << ex.what() << "\n";
    }
}

int main() {
    TestFormulaParser();
    TestSubstitution();
    TestModusPonens();
    TestModusTollens();
    TestDisjunctiveSyllogism();
    TestHypotheticalSyllogism();
    TestSimpleConstructiveDilemma();
    TestComplexConstructiveDilemma();
    TestSimpleDestructiveDilemma();
    TestComplexDestructiveDilemma();
    return 0;
}
