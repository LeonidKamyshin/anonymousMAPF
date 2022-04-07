#include "mincost.h"

MinCostSolver::MinCostSolver(const std::vector<Edge> &edges, int _source, int _sink, int _maxEdgeId)
        : s(_source)
        , t(_sink)
        , maxEdgeId(_maxEdgeId)
{
    gr.resize(maxEdgeId);
    dist.resize(maxEdgeId);
    par.resize(maxEdgeId);
    phi.resize(maxEdgeId);
    for(auto edge:edges){
        addEdge(edge.start, edge.end, edge.capacity, edge.cost);
    }
}

void MinCostSolver::addEdge(int from, int to, int c, int cost) {
    Edge tmp = Edge(from, to, 0, c, cost);
    gr[from].push_back(e.size());
    e.push_back(tmp);
    tmp.start = to;
    tmp.end = from;
    tmp.flow = 0;
    tmp.capacity = 0;
    tmp.cost *= -1;
    gr[to].push_back(e.size());
    e.push_back(tmp);
}

std::vector<Edge> MinCostSolver::getEdges() {
    return e;
}

void MinCostSolver::fordBellman() {
    for (int i = 0; i < maxEdgeId; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    while (true) {
        bool change = false;
        for (int i = 0; i < e.size(); i++) {
            if (e[i].flow != e[i].capacity && dist[e[i].end] > dist[e[i].start] + e[i].cost) {
                change = true;
                dist[e[i].end] = dist[e[i].start] + e[i].cost;
            }
        }
        if (!change) {
            break;
        }
    }
}

bool MinCostSolver::dijstra() {
    for (int i = 0; i < maxEdgeId; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        cur.first *= -1;
        if(cur.first > dist[cur.second]){
            continue;
        }
        for (int i = 0; i < gr[cur.second].size(); i++) {
            int id = gr[cur.second][i];
            if(e[id].flow == e[id].capacity){
                continue;
            }
            int to = e[id].end;
            int w = phi[cur.second] - phi[to] + e[id].cost;
            if(dist[to] > cur.first + w){
                dist[to] = cur.first + w;
                par[to] = id;
                q.push({-dist[to],to});
            }
        }
    }
    return dist[s] != INF;
}

int MinCostSolver::minCost()
{
    fordBellman();
    for(int i = 0; i < maxEdgeId;i++){
        phi[i] = dist[i];
    }
    int ans = 0;
    while(true)
    {
        dijstra();
        if(dist[t] == INF) {
            break;
        }
        for(int i = 0; i < maxEdgeId;i++){
            phi[i] = std::min(static_cast<int>(1000000000),dist[i] + phi[i]);
        }

        int cur = t;
        int maxFlow = INF;
        while(cur != s){
            int id = par[cur];
            maxFlow = std::min(maxFlow,e[id].capacity-e[id].flow);
            cur = e[id].start;
        }
        cur = t;
        while(cur != s)
        {
            int id = par[cur];
            e[id].flow += maxFlow;
            e[id^1].flow -= maxFlow;
            ans += e[id].cost*maxFlow;
            cur = e[id].start;
        }
    }
    return ans;
}