#ifndef ANONYMOUSMAPF_TIMEEXPANDEDNETWORK_H
#define ANONYMOUSMAPF_TIMEEXPANDEDNETWORK_H

#include <map>
#include "network.h"
#include "searchresult.h"
#include <unordered_map>

class TimeExpandedNetwork {
public:
    TimeExpandedNetwork(const Map &_map, int _time);

    void addSuperSource(std::vector<int> start_x, std::vector<int> start_y);

    void addSuperSink(std::vector<int> finish_x, std::vector<int> finish_y);

    int translateCoord(int _id, int _time);

    int getSource();

    int getSink();

    int getTime();

    std::vector<Edge> getEdges();

    std::pair<std::pair<int,int>, int> retrieveEdge(int from, int to);

    SearchResult convertPath(const std::vector<int>& path);

private:
    void buildTimeExpandedNetwork(const Map &map);

    void addEdge(int start, int end, int capacity, int cost);

    void createTimestep(int a, int b);

    int translateOutgoingFictiveNode(int a, int b, int timestep);

    int translateIncomingFictiveNode(int a, int b, int timestep);

    void addIdleEdges(int _node);

    Network init_network;
    int time, source, sink, maxid;
    std::map<std::pair<int, int>, int> time_translations;
    std::unordered_map<int, std::pair<int,int>> node_reverse_translations;
    std::map<std::pair<int, int>, int> outgoing_fictive_nodes;
    std::unordered_map<int, std::pair<int,int>> outgoing_nodes_reverse_translations;
    std::map<std::pair<int, int>, int> incoming_fictive_nodes;
    std::unordered_map<int, std::pair<int,int>> incoming_nodes_reverse_translations;
    std::vector<Edge> graph;

};

#endif //ANONYMOUSMAPF_TIMEEXPANDEDNETWORK_H
