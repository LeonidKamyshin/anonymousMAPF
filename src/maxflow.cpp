#include "maxflow.h"

MaxFlowSolver::MaxFlowSolver(const std::vector<Edge>& edges, int _source, int _sink, int _maxEdgeId)
    : s(_source)
    , t(_sink)
    , maxEdgeId(_maxEdgeId)
{
    gr.resize(maxEdgeId);
    dist.resize(maxEdgeId);
    p.resize(maxEdgeId);
    for(auto edge:edges){
        addEdge(edge.start, edge.end, edge.capacity, edge.cost);
    }
}

void MaxFlowSolver::addEdge(int from, int to, int c, int cost)
{
    Edge tmp(from, to, 0, c, cost);
    gr[from].push_back(e.size());
    e.push_back(tmp);
    tmp.start = to;
    tmp.end = from;
    tmp.capacity = 0;
    tmp.cost = cost;
    gr[to].push_back(e.size());
    e.push_back(tmp);
}

bool MaxFlowSolver::bfs()
{
    for(int i = 0; i < maxEdgeId;i++){
        dist[i] = INF;
    }
    dist[s] = 0;
    q.push(s);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i = 0; i < gr[v].size();i++){
            int id = gr[v][i];
            int cur = e[id].end;
            if(dist[v] + 1 < dist[cur] && e[id].flow + flow <= e[id].capacity){
                dist[cur] = dist[v] + 1;
                q.push(cur);
            }
        }
    }
    return dist[t] != INF;
}
bool MaxFlowSolver::dfs(int v)
{
    for(; p[v] < gr[v].size();p[v]++){
        int id = gr[v][p[v]];
        int cur = e[id].end;
        if(dist[v] + 1 == dist[cur] && e[id].flow + flow <= e[id].capacity){
            if(dfs(cur)){
                e[id].flow += flow;
                e[id^1].flow -= flow;
                return true;
            }
        }
    }
    return v == t;
}

int MaxFlowSolver::Dinica()
{
    int answer = 0;
    flow = 1e9;
    while(flow > 0){
        while(bfs()){
            for(int i = 0; i < maxEdgeId;i++){
                p[i] = 0;
            }
            while(dfs(s)){
                answer += flow;
            }
        }
        flow>>=1;
    }
    return answer;
}

std::vector<Edge> MaxFlowSolver::getEdges() {
    return e;
}
