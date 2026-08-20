#include "aegis/solver.hpp"
#include <cassert>
#include <iostream>

int main() {
    aegis::Policy p;
    p.maximum_loss["ETH"] = 1.01;
    p.minimum_delta["USDC"] = 3300;

    std::vector<aegis::WorldOutcome> safe = {
        {"a", "sim-a", 1.0, 0.0, {{"ETH", -1.0},{"USDC",3400}}, {}, false,false,false,false},
        {"b", "sim-b", 0.9, 0.1, {{"ETH", -1.0},{"USDC",3350}}, {}, false,false,false,false}
    };
    auto ok = aegis::assess_transaction(safe, p);
    assert(ok.decision == aegis::Decision::Allow);
    assert(ok.counterexample_world.empty());

    auto bad = safe;
    bad.push_back({"evil", "sim-c", 0.8, 0.02, {{"ETH",-1.0},{"USDC",0}}, {{"USDC","spender",0,true}}, false,false,false,false});
    auto blocked = aegis::assess_transaction(bad, p);
    assert(blocked.decision == aegis::Decision::Block);
    assert(blocked.counterexample_world == "evil");
    assert(!blocked.counterexample_violations.empty());

    std::vector<aegis::WorldOutcome> low = {{"low", "sim-x", 0.1, 0, {}, {}, false,false,false,false}};
    auto unknown = aegis::assess_transaction(low, p);
    assert(unknown.decision == aegis::Decision::Unknown);
    std::cout << "CAPE-Σ C++ tests passed\n";
}
