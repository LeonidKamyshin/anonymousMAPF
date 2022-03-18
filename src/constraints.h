#ifndef ANONYMOUSMAPF_CONSTRAINTS_H
#define ANONYMOUSMAPF_CONSTRAINTS_H
#include <unordered_map>
#include <set>
class Constraints{
public:
    Constraints();
    Constraints(Constraints& _constraints);
    Constraints extend(int id, int timestep, std::pair<int,int> coords);
    std::unordered_map<int, std::set<std::pair<int,int>>> getConstraints(const int id);
private:
    std::unordered_map<int, std::unordered_map<int, std::set<std::pair<int,int>>>> constraints;
};
#endif //ANONYMOUSMAPF_CONSTRAINTS_H
