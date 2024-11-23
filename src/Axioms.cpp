#include "Axioms.h"

std::vector<std::shared_ptr<Node>> Axioms::GetAxioms1To3()
{
    return {A1(), A2(), A3()};
}

std::vector<std::shared_ptr<Node>> Axioms::GetAxioms4To11()
{
    return {A4(), A5(), A6(), A7(), A8(), A9(), A10(), A11()};
}

std::shared_ptr<Node> Axioms::A1() {
    return FormulaParser::Parse("(A>(B>A))");
}

std::shared_ptr<Node> Axioms::A2() {
    return FormulaParser::Parse("((A>(B>C))>((A>B)>(A>C)))");
}

std::shared_ptr<Node> Axioms::A3() {
    return FormulaParser::Parse("((!B>!A)>((!B>A)>B))");
}

std::shared_ptr<Node> Axioms::A4()
{
    return FormulaParser::Parse("(A*B)>A");
}

std::shared_ptr<Node> Axioms::A5()
{
    return FormulaParser::Parse("(A*B)>B");
}

std::shared_ptr<Node> Axioms::A6()
{
    return FormulaParser::Parse("A>(B>(A*B))");
}

std::shared_ptr<Node> Axioms::A7()
{
    return FormulaParser::Parse("A>(A|B)");
}

std::shared_ptr<Node> Axioms::A8()
{
    return FormulaParser::Parse("B>(A|B)");
}

std::shared_ptr<Node> Axioms::A9()
{
    return FormulaParser::Parse("(A>C)>((B>C)>((A|B)>C))");
}

std::shared_ptr<Node> Axioms::A10()
{
    return FormulaParser::Parse("!A>(A>B)");
}

std::shared_ptr<Node> Axioms::A11()
{
    return FormulaParser::Parse("A|!A");
}
