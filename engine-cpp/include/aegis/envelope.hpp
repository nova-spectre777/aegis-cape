#pragma once
#include "aegis/model.hpp"
#include <map>
#include <string>
#include <vector>

namespace aegis {
std::map<std::string, EnvelopeRange> build_envelope(const std::vector<WorldOutcome>& worlds, double min_credibility);
double disagreement_entropy(const std::vector<WorldOutcome>& worlds, double min_credibility);
std::string world_signature(const WorldOutcome& world);
}
