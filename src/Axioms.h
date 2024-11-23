#ifndef AXIOMS_H
#define AXIOMS_H

#include "FormulaParser.h"
#include <vector>

class Axioms {
public:
    // Возвращает список аксиом с 1 по 3
    static std::vector<std::shared_ptr<Node>> GetAxioms1To3();
    
    // Возвращает список аксиом с 4 по 11
    static std::vector<std::shared_ptr<Node>> GetAxioms4To11();

    static std::shared_ptr<Node> A1();
    static std::shared_ptr<Node> A2();
    static std::shared_ptr<Node> A3();

    static std::shared_ptr<Node> A4();
    static std::shared_ptr<Node> A5();
    static std::shared_ptr<Node> A6();
    static std::shared_ptr<Node> A7();
    static std::shared_ptr<Node> A8();
    static std::shared_ptr<Node> A9();
    static std::shared_ptr<Node> A10();
    static std::shared_ptr<Node> A11();
};

#endif