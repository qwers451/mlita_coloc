#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <memory>
#include <iostream>
#include <sstream>

enum class NodeType {
    VARIABLE,
    OPERATOR
};

struct Node {
    NodeType type;                     
    std::string value;                 
    std::shared_ptr<Node> left = nullptr;  
    std::shared_ptr<Node> right = nullptr; 

    explicit Node(const std::string& val) : type(NodeType::VARIABLE), value(val) {}

    Node(const std::string& val, std::shared_ptr<Node> l, std::shared_ptr<Node> r = nullptr)
        : type(NodeType::OPERATOR), value(val), left(std::move(l)), right(std::move(r)) {}

    // Рекурсивно выводит дерево узлов с отступами для наглядности
    void printTree(int indent = 0);

    // Преобразует дерево узлов в строковое представление формулы
    std::string toString();
};

#endif
