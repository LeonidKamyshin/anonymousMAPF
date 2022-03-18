#ifndef ANONYMOUSMAPF_NETWORK_H
#define ANONYMOUSMAPF_NETWORK_H

#include <vector>
#include <map>
#include "edge.h"
#include "map.h"
#include <unordered_map>

class Network {
public:
    Network(const Map &_map);

    int translateCoord(int x, int y);

    void addEdge(int start, int end);

    [[nodiscard]] std::vector<Edge> getGraph() const;

    [[nodiscard]] std::map<std::pair<int, int>, int> getNodes() const;

    std::pair<int,int> convertEdge(int node);

    constexpr static const std::pair<int, int> source = {-1, 0};
    constexpr static const std::pair<int, int> sink = {0, -1};

private:
    void buildNetwork(const Map &map);

    std::vector<Edge> graph;
    std::map<std::pair<int, int>, int> translation;
    std::unordered_map<int, std::pair<int,int>> reverse_translation;
};

#endif //ANONYMOUSMAPF_NETWORK_H
