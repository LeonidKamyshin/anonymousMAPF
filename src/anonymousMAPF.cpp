#include <iostream>
#include <algorithm>

#include "anonymousMAPF.h"
#include "maxflow.h"
#include "mincost.h"
#include "astaroptions.h"
#include "astar.h"
#include "xmltags.h"

std::vector<SearchResult> AnonymousMAPF::search(const Map &map) {
    if(map.objective == TAG_MT_AVGTIME){
        return searchAvgTimeObjective(map);
    }
    else if(map.objective == TAG_MT_MAKESPAN){
        return searchMakespanObjective(map);
    }
    else if(map.objective == TAG_MT_AVGDIST){
        return searchAvgDistanceObjective(map);
    }
    return vector<SearchResult>();
}

std::vector<SearchResult> AnonymousMAPF::searchMakespanObjective(const Map &map) {
    int L = 0, mid, R = map.agents_count + AnonymousMAPF::getL(map);
    while (R - L > 1) {
        mid = (L + R - 1) / 2;
        TimeExpandedNetwork network = TimeExpandedNetwork(map, mid, 1);
        MaxFlowSolver max_flow_solver = MaxFlowSolver(network.getEdges(), network.getSource(), network.getSink(),
                                                      network.getMaxEdgeId() + 1);
        if (max_flow_solver.Dinica() == map.agents_count) {
            R = mid + 1;
        } else {
            L = mid + 1;
        }
    }

    TimeExpandedNetwork network = TimeExpandedNetwork(map, L, 1);
    MaxFlowSolver max_flow_solver = MaxFlowSolver(network.getEdges(), network.getSource(), network.getSink(),
                                                  network.getMaxEdgeId() + 1);
    std::cout << "Makespan is: " << L << '\n';
    std::cout << "Agents found destination: " << max_flow_solver.Dinica() << '\n';
    return retrievePath(max_flow_solver.getEdges(), network);
}

std::vector<SearchResult> AnonymousMAPF::searchAvgTimeObjective(const Map& map){
    int L = 0, mid, R = (map.agents_count-1)*(map.agents_count-2)/2 + map.V + 1;
    while(R - L > 1){
        mid = (L+R-1)/2;
        TimeExpandedNetwork network = TimeExpandedNetwork(map, mid, 1);
        MinCostSolver min_cost_solver = MinCostSolver(network.getEdges(), network.getSource(), network.getSink(),
                                                      network.getMaxEdgeId() + 1);
        min_cost_solver.minCost();
        int reached = 0;
        for(auto &edge:min_cost_solver.getEdges()){
            if(edge.end == network.getSink() && edge.flow == 1){
                reached += 1;
            }
        }
        if(reached == map.agents_count){
            R = mid + 1;
        }
        else{
            L = mid + 1;
        }
    }
    TimeExpandedNetwork network = TimeExpandedNetwork(map, L, 1);
    MinCostSolver min_cost_solver = MinCostSolver(network.getEdges(), network.getSource(), network.getSink(),
                                                  network.getMaxEdgeId() + 1);
    std::cout << "Total cost is:" << min_cost_solver.minCost() << '\n';
    return retrievePath(min_cost_solver.getEdges(), network);
}

std::vector<SearchResult> AnonymousMAPF::searchAvgDistanceObjective(const Map &map) {
    int T = map.agents_count + AnonymousMAPF::getL(map) - 1;
    TimeExpandedNetwork network = TimeExpandedNetwork(map, T, 0);
    MinCostSolver min_cost_solver = MinCostSolver(network.getEdges(), network.getSource(), network.getSink(),
                                                  network.getMaxEdgeId() + 1);
    std::cout << "Total cost is:" << min_cost_solver.minCost() << '\n';
    int reached = 0;
    for(auto &edge:min_cost_solver.getEdges()){
        if(edge.end == network.getSink() && edge.flow == 1){
            reached += 1;
        }
    }
    std::cout << "Agents found path: " << reached << '\n';
    return retrievePath(min_cost_solver.getEdges(), network);
}

std::vector<SearchResult> AnonymousMAPF::retrievePath(const vector<Edge> &edges, TimeExpandedNetwork &network) {
    std::vector<std::vector<std::pair<int, int>>> networkEdges(2 * network.getTime() + 2);
    for (auto edge: edges) {
        if (edge.flow != 1) {
            continue;
        }
        std::pair<std::pair<int, int>, int> real_edge = network.retrieveEdge(edge.start, edge.end);
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

    // Отсекаем начало в случаях когда все агенты стоят на месте
    int min_idx = 1e9;
    for(int i = 0; i < paths.size(); ++i){
        min_idx = std::min(static_cast<int>(paths[i].size()), min_idx);
    }
    int start_idx = 0;
    bool idle = true;
    for(int i = 1 ; i < min_idx && idle; ++i){
        for(int j = 0; j < paths.size(); ++j){
            if(paths[j][i] != paths[j][i-1]){
                start_idx = i;
                idle = false;
                break;
            }
        }
    }
    for(int j = 0; j < paths.size(); ++j){
        paths[j] = std::vector<int>(paths[j].begin() + start_idx, paths[j].end());
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
        for (int j = 0; j < map.agents_count; ++j) {
            AStar astar((AStarOptions(MetricType::Euclidean)));
            SearchRequest request(map.start_x[i], map.start_y[i], map.finish_x[j], map.finish_y[j]);
            maxlen = std::max(static_cast<int>(astar.findPath(map, request).path.size()), maxlen);
        }
    }
    return maxlen;
}


