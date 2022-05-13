#ifndef ANONYMOUSMAPF_ANONYMOUSMAPF_H
#define ANONYMOUSMAPF_ANONYMOUSMAPF_H

#include <vector>
#include "searchresult.h"
#include "map.h"
#include "edge.h"
#include "timeexpandednetwork.h"

class AnonymousMAPFSolver {
public:
    std::vector<SearchResult> search(const Map& map);

private:
    std::vector<SearchResult> retrievePath(const std::vector<Edge>& edges, TimeExpandedNetwork& network);

    std::vector<SearchResult> searchTimespanObjective(const Map& map);
    std::vector<SearchResult> searchAvgDistanceObjective(const Map &map);

    int getL(const Map& map);
};
#endif //ANONYMOUSMAPF_ANONYMOUSMAPF_H
