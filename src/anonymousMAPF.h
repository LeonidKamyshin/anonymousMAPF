#ifndef ANONYMOUSMAPF_ANONYMOUSMAPF_H
#define ANONYMOUSMAPF_ANONYMOUSMAPF_H

#include <vector>
#include "searchresult.h"
#include "map.h"
#include "maxflowedge.h"
#include "timeexpandednetwork.h"

class AnonymousMAPF {
public:
    std::vector<SearchResult> search(const Map& map);

private:
    std::vector<SearchResult> retrievePath(const std::vector<MaxFlowEdge>& edges, TimeExpandedNetwork& network);

    int getL(const Map& map);
};
#endif //ANONYMOUSMAPF_ANONYMOUSMAPF_H
