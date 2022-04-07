#ifndef ANONYMOUSMAPF_MINCOST_H
#define ANONYMOUSMAPF_MINCOST_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
#include <iomanip>

#include "edge.h"

class MinCostSolver {
public:
    MinCostSolver(const std::vector<Edge> &edges, int _source, int _sink, int _maxEdgeId);
    int minCost();
    std::vector<Edge> getEdges();

private:
    void addEdge(int from, int to, int c, int cost);
    void fordBellman();
    bool dijstra();

    static const int INF = 1e9;
    int maxEdgeId;
    std::vector<Edge> e;
    std::vector<std::vector<int>> gr;
    int s, t, flow;
    std::vector<int> dist, phi, par;
    std::priority_queue<std::pair<int, int>> q;
};

#endif //ANONYMOUSMAPF_MINCOST_H
