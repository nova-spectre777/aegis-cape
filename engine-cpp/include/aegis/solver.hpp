#pragma once
#include "aegis/model.hpp"
#include <string>
#include <vector>

namespace aegis {
std::vector<Violation> evaluate_world(const WorldOutcome& world, const Policy& policy);
Assessment assess_transaction(const std::vector<WorldOutcome>& worlds, const Policy& policy);
std::string decision_name(Decision decision);
}
