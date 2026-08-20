#include "aegis/solver.hpp"
#include "aegis/envelope.hpp"
#include <algorithm>
#include <limits>

namespace aegis {

static double delta_for(const WorldOutcome& world, const std::string& asset) {
    for (const auto& d : world.asset_deltas) if (d.asset == asset) return d.delta;
    return 0.0;
}

std::vector<Violation> evaluate_world(const WorldOutcome& world, const Policy& policy) {
    std::vector<Violation> v;
    for (const auto& [asset, minimum] : policy.minimum_delta) {
        const auto actual = delta_for(world, asset);
        if (actual < minimum) {
            v.push_back({"MINIMUM_DELTA", asset + " delta below allowed minimum", Severity::Critical});
        }
    }
    for (const auto& [asset, max_loss] : policy.maximum_loss) {
        const auto actual = delta_for(world, asset);
        if (actual < -max_loss) {
            v.push_back({"MAXIMUM_LOSS", asset + " loss exceeds policy", Severity::Critical});
        }
    }
    if (policy.deny_unlimited_approvals) {
        for (const auto& a : world.approvals) {
            if (a.unlimited) v.push_back({"UNLIMITED_APPROVAL", "unlimited approval introduced for " + a.token, Severity::Critical});
        }
    }
    if (policy.deny_owner_change && world.owner_changed)
        v.push_back({"OWNER_CHANGE", "wallet owner set changes", Severity::Critical});
    if (policy.deny_module_install && world.module_installed)
        v.push_back({"MODULE_INSTALL", "wallet module installation detected", Severity::Critical});
    if (policy.deny_delegatecall && world.delegatecall_used)
        v.push_back({"DELEGATECALL", "delegatecall observed in adversarial world", Severity::High});
    if (policy.deny_codehash_change && world.codehash_changed)
        v.push_back({"CODEHASH_CHANGE", "target implementation code hash changed", Severity::High});
    return v;
}

Assessment assess_transaction(const std::vector<WorldOutcome>& worlds, const Policy& policy) {
    Assessment result;
    result.observed_envelope = build_envelope(worlds, policy.minimum_credible_world);
    result.disagreement_entropy = disagreement_entropy(worlds, policy.minimum_credible_world);

    bool any_credible = false;
    double best_cost = std::numeric_limits<double>::infinity();
    for (const auto& world : worlds) {
        if (world.credibility < policy.minimum_credible_world) continue;
        any_credible = true;
        auto violations = evaluate_world(world, policy);
        result.worlds.push_back({world, violations});
        if (!violations.empty() && world.perturbation_cost < best_cost) {
            best_cost = world.perturbation_cost;
            result.counterexample_world = world.id;
            result.counterexample_violations = violations;
        }
    }
    if (!any_credible) result.decision = Decision::Unknown;
    else if (!result.counterexample_world.empty()) result.decision = Decision::Block;
    else result.decision = Decision::Allow;
    return result;
}

std::string decision_name(Decision decision) {
    switch (decision) {
        case Decision::Allow: return "ALLOW";
        case Decision::Block: return "BLOCK";
        default: return "UNKNOWN";
    }
}

} // namespace aegis
