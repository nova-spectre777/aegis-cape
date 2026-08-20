#include "aegis/solver.hpp"
#include <iostream>

int main() {
    aegis::Policy policy;
    policy.maximum_loss["ETH"] = 1.01;
    policy.minimum_delta["USDC"] = 3350.0;

    std::vector<aegis::WorldOutcome> worlds = {
        {"baseline", "sim-a", 1.0, 0.0, {{"ETH", -1.0}, {"USDC", 3420}}, {}, false, false, false, false},
        {"oracle-shift", "sim-b", 0.9, 0.15, {{"ETH", -1.0}, {"USDC", 3375}}, {}, false, false, false, false},
        {"router-upgrade", "sim-c", 0.8, 0.05, {{"ETH", -1.0}, {"USDC", 0}}, {{"USDC", "0xattacker", 0, true}}, false, false, false, true}
    };

    auto result = aegis::assess_transaction(worlds, policy);
    std::cout << "decision=" << aegis::decision_name(result.decision) << "\n";
    std::cout << "entropy=" << result.disagreement_entropy << "\n";
    std::cout << "counterexample=" << result.counterexample_world << "\n";
    for (const auto& v : result.counterexample_violations) std::cout << v.code << ": " << v.message << "\n";
}
