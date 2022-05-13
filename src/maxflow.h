#ifndef ANONYMOUSMAPF_MAXFLOW_H
#define ANONYMOUSMAPF_MAXFLOW_H

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

using namespace std;

class MaxFlowSolver {
public:
    MaxFlowSolver(const std::vector<Edge> &edges, int _source, int _sink, int _maxEdgeId);

    int MaxFlow();

    std::vector<Edge> getEdges();

private:
    void addEdge(int from, int to, int c, int cost);

    bool bfs();

    bool dfs(int v);

    static const int INF = 1e9;
    int maxEdgeId;
    std::vector<Edge> e;
    std::vector<vector<int>> gr;
    int s, t, flow;
    std::vector<int> dist, p;
    queue<int> q;
};

#endif //ANONYMOUSMAPF_MAXFLOW_H
