#include "constraints.h"

Constraints::Constraints() {}

Constraints::Constraints(Constraints& _constraints) {
    constraints = _constraints.constraints;
}
Constraints Constraints::extend(int id, int timestep, std::pair<int, int> coords) {
    auto extended_constraints = Constraints(*this);
    extended_constraints.constraints.at(id).at(timestep).insert(coords);
    return extended_constraints;
}

std::unordered_map<int, std::set<std::pair<int, int>>> Constraints::getConstraints(const int id) {
    return constraints.at(id);
}
