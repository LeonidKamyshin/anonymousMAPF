#include <iostream>
#include <algorithm>

#include "anonymousMAPF.h"
#include "maxflow.h"
#include "astaroptions.h"
#include "astar.h"

std::vector<SearchResult> AnonymousMAPF::search(const Map &map) {
    int L = 0, mid, R = map.agents_count + AnonymousMAPF::getL(map);
    while (R - L > 1) {
        mid = (L + R - 1) / 2;
        TimeExpandedNetwork network = TimeExpandedNetwork(map, mid);
        MaxFlowSolver max_flow_solver = MaxFlowSolver(network.getEdges(), network.getSource(), network.getSink());
        if (max_flow_solver.Dinica() == map.agents_count) {
            R = mid + 1;
        } else {
            L = mid + 1;
        }
    }

    TimeExpandedNetwork network = TimeExpandedNetwork(map, L);
    MaxFlowSolver max_flow_solver = MaxFlowSolver(network.getEdges(), network.getSource(), network.getSink());
    std::cout << "Timespan is: " << L << '\n';
    std::cout << "Agents found destination: " << max_flow_solver.Dinica() << '\n';
    return retrievePath(max_flow_solver.getEdges(), network);
}

std::vector<SearchResult> AnonymousMAPF::retrievePath(const vector<MaxFlowEdge> &edges, TimeExpandedNetwork &network) {
    std::vector<std::vector<std::pair<int, int>>> networkEdges(2 * network.getTime() + 2);
    for (auto edge: edges) {
        if (edge.f != 1) {
            continue;
        }
        std::pair<std::pair<int, int>, int> real_edge = network.retrieveEdge(edge.from, edge.to);
        if (real_edge.second == -1) {
            continue;
        }
        networkEdges[real_edge.second].push_back(real_edge.first);
    }

    std::vector<std::vector<int>> paths(networkEdges[1].size());
    std::map<int, int> lastNode, curNode;
    for (int i = 0; i < networkEdges.size(); ++i) {
        for (int j = 0; j < networkEdges[i].size(); ++j) {
            std::pair<int, int> curEdge = networkEdges[i][j];
            if (i == 1) {
                paths[j].push_back(curEdge.first);
                paths[j].push_back(curEdge.second);
                curNode[curEdge.second] = j;
            } else {
                int idx = lastNode[curEdge.first];
                paths[idx].push_back(curEdge.second);
                curNode[curEdge.second] = idx;
            }
        }
        lastNode = curNode;
    }

    std::vector<SearchResult> answer;
    for (int i = 0; i < paths.size(); ++i) {
        answer.push_back(network.convertPath(paths[i]));
    }
    return answer;
}

int AnonymousMAPF::getL(const Map &map) {
    int maxlen = 0;
    for (int i = 0; i < map.agents_count; ++i) {
        for (int j = i + 1; j < map.agents_count; ++j) {
            AStar astar((AStarOptions(MetricType::Euclidean)));
            SearchRequest request(map.start_x[i], map.start_y[i], map.finish_x[j], map.finish_y[j]);
            maxlen = std::max(static_cast<int>(astar.findPath(map, request).path.size()), maxlen);
        }
    }
    return maxlen;
}
