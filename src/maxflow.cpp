#include "maxflow.h"

MaxFlowSolver::MaxFlowSolver(const std::vector<Edge>& edges, int _source, int _sink)
    : s(_source)
    , t(_sink)
{
    for(auto edge:edges){
        addEdge(edge.start, edge.end, edge.capacity);
    }
}

void MaxFlowSolver::addEdge(int from, int to, int c)
{
    MaxFlowEdge tmp(from,to,0,c);
    gr[from].push_back(e.size());
    e.push_back(tmp);
    tmp.from = to;
    tmp.to = from;
    tmp.c = 0;
    gr[to].push_back(e.size());
    e.push_back(tmp);
}

bool MaxFlowSolver::bfs()
{
    for(int i = 0; i < MAXN;i++){
        dist[i] = INF;
    }
    dist[s] = 0;
    q.push(s);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i = 0; i < gr[v].size();i++){
            int id = gr[v][i];
            int cur = e[id].to;
            if(dist[v] + 1 < dist[cur] && e[id].f + flow <= e[id].c){
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
        int cur = e[id].to;
        if(dist[v] + 1 == dist[cur] && e[id].f + flow <= e[id].c){
            if(dfs(cur)){
                e[id].f += flow;
                e[id^1].f -= flow;
                return true;
            }
        }
    }
    return v == t;
}

int MaxFlowSolver::Dinica()
{
    int answer = 0;
    flow = 1;
    while(flow > 0){
        while(bfs()){
            for(int i = 0; i <= MAXN;i++){
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

std::vector<MaxFlowEdge> MaxFlowSolver::getEdges() {
    return e;
}
