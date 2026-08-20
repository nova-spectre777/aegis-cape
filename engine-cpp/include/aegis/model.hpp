#pragma once
#include <map>
#include <string>
#include <vector>

namespace aegis {

enum class Decision { Allow, Block, Unknown };

enum class Severity { Info = 0, Warning = 1, High = 2, Critical = 3 };

struct AssetDelta {
    std::string asset;
    double delta{0.0};
};

struct ApprovalChange {
    std::string token;
    std::string spender;
    double amount{0.0};
    bool unlimited{false};
};

struct WorldOutcome {
    std::string id;
    std::string simulator;
    double credibility{1.0};
    double perturbation_cost{0.0};
    std::vector<AssetDelta> asset_deltas;
    std::vector<ApprovalChange> approvals;
    bool owner_changed{false};
    bool module_installed{false};
    bool delegatecall_used{false};
    bool codehash_changed{false};
};

struct Policy {
    std::map<std::string, double> minimum_delta;
    std::map<std::string, double> maximum_loss;
    bool deny_unlimited_approvals{true};
    bool deny_new_operators{true};
    bool deny_owner_change{true};
    bool deny_module_install{true};
    bool deny_delegatecall{true};
    bool deny_codehash_change{false};
    double minimum_credible_world{0.5};
};

struct Violation {
    std::string code;
    std::string message;
    Severity severity{Severity::Warning};
};

struct WorldAssessment {
    WorldOutcome world;
    std::vector<Violation> violations;
};

struct EnvelopeRange {
    double min_delta{0.0};
    double max_delta{0.0};
};

struct Assessment {
    Decision decision{Decision::Unknown};
    std::vector<WorldAssessment> worlds;
    std::map<std::string, EnvelopeRange> observed_envelope;
    double disagreement_entropy{0.0};
    std::string counterexample_world;
    std::vector<Violation> counterexample_violations;
};

} // namespace aegis
