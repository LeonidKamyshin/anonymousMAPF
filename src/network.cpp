#include "network.h"

Network::Network(const Map &_map) {
    buildNetwork(_map);
}

void Network::buildNetwork(const Map &map) {
    for (int x = 0; x < map.getMapHeight(); ++x) {
        for (int y = 0; y < map.getMapWidth(); ++y) {
            if (!map.CellIsTraversable(x, y)) {
                continue;
            }
            int cur_node = translateCoord(x, y);
            if (map.CellOnGrid(x + 1, y) && map.CellIsObstacle(x + 1, y)) {
                int next_node = translateCoord(x + 1, y);
                addEdge(cur_node, next_node);
            }
            if (map.CellOnGrid(x, y + 1) && map.CellIsTraversable(x, y + 1)) {
                int next_node = translateCoord(x, y + 1);
                addEdge(cur_node, next_node);
            }
        }
    }
}

int Network::translateCoord(int x, int y) {
    if (Network::translation.contains({x, y})) {
        return Network::translation[{x, y}];
    } else {
        Network::translation[{x, y}] = static_cast<int>(Network::translation.size());
        reverse_translation[translation[{x, y}]] = {x, y};
        return translation[{x, y}];
    }
}

void Network::addEdge(int start, int end) {
    Network::graph.emplace_back(Edge(start, end, 0, 0, 0));
}

std::vector<Edge> Network::getGraph() const {
    return graph;
}

std::map<std::pair<int, int>, int> Network::getNodes() const {
    return translation;
}

std::pair<int, int> Network::convertEdge(int node) {
    return reverse_translation[node];
}
