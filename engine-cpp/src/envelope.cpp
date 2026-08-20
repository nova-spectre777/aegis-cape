#include "aegis/envelope.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <map>
#include <sstream>

namespace aegis {

std::map<std::string, EnvelopeRange> build_envelope(const std::vector<WorldOutcome>& worlds, double min_credibility) {
    std::map<std::string, EnvelopeRange> result;
    std::map<std::string, bool> seen;
    for (const auto& world : worlds) {
        if (world.credibility < min_credibility) continue;
        for (const auto& delta : world.asset_deltas) {
            if (!seen[delta.asset]) {
                result[delta.asset] = {delta.delta, delta.delta};
                seen[delta.asset] = true;
            } else {
                auto& r = result[delta.asset];
                r.min_delta = std::min(r.min_delta, delta.delta);
                r.max_delta = std::max(r.max_delta, delta.delta);
            }
        }
    }
    return result;
}

std::string world_signature(const WorldOutcome& world) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(6);
    std::vector<AssetDelta> deltas = world.asset_deltas;
    std::sort(deltas.begin(), deltas.end(), [](const auto& a, const auto& b){ return a.asset < b.asset; });
    for (const auto& d : deltas) out << d.asset << ':' << d.delta << ';';
    out << "owner=" << world.owner_changed
        << ";module=" << world.module_installed
        << ";delegate=" << world.delegatecall_used
        << ";codehash=" << world.codehash_changed;
    for (const auto& a : world.approvals) {
        out << ";approval=" << a.token << ':' << a.spender << ':' << a.amount << ':' << a.unlimited;
    }
    return out.str();
}

double disagreement_entropy(const std::vector<WorldOutcome>& worlds, double min_credibility) {
    std::map<std::string, double> mass;
    double total = 0.0;
    for (const auto& w : worlds) {
        if (w.credibility < min_credibility) continue;
        const double weight = std::max(0.0, w.credibility);
        mass[world_signature(w)] += weight;
        total += weight;
    }
    if (total <= 0 || mass.size() <= 1) return 0.0;
    double h = 0.0;
    for (const auto& [_, m] : mass) {
        const double p = m / total;
        h -= p * std::log2(p);
    }
    const double max_h = std::log2(static_cast<double>(mass.size()));
    return max_h > 0 ? h / max_h : 0.0;
}

} // namespace aegis
