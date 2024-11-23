#include "src/TheoremProver.h"

int main() {
    TheoremProver prover;

    std::vector<std::string> targets = {
        // "(A * B) > A",       // A4
        // "(A * B) > B",       // A5
        // "A > (B > (A * B))", // A6
        // "A > (A | B)",       // A7
        // "B > (A | B)",       // A8
        // "(A > C) > ((B > C) > ((A | B) > C))", // A9
        // "!A > (A > B)",      // A10
        "A | !A"             // A11
    };

    for (const auto& targetStr : targets) {
        auto target = FormulaParser::Parse(targetStr);
        if (prover.Prove(target)) {
            std::cout << "The identity of " << targetStr << " has been proven!\n";
        } else {
            std::cout << "Failed to prove the identity: " << targetStr << "\n";
        }
    }

    return 0;
}
