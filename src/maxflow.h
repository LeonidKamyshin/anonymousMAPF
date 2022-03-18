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
#include "maxflowedge.h"

using namespace std;
class MaxFlowSolver{
public:
    MaxFlowSolver(const std::vector<Edge>& edges, int _source, int _sink);

    int Dinica();

    std::vector<MaxFlowEdge> getEdges();
private:
    void addEdge(int from, int to, int c);

    bool bfs();

    bool dfs(int v);

    static const int MAXN = 2500, INF = 1e9;
    vector<MaxFlowEdge> e;
    vector<int> gr[MAXN];
    int s,t, flow;
    int dist[MAXN],p[MAXN];
    queue<int> q;

};

#endif //ANONYMOUSMAPF_MAXFLOW_H
