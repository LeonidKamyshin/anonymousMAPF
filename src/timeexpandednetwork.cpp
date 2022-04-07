#include <iostream>
#include "timeexpandednetwork.h"

TimeExpandedNetwork::TimeExpandedNetwork(const Map &_map, int _time, int _holdover_edge_cost)
        : init_network(Network(_map))
        , time(_time)
        , holdover_edge_cost(_holdover_edge_cost)
{
    TimeExpandedNetwork::buildTimeExpandedNetwork(_map);
}

void TimeExpandedNetwork::buildTimeExpandedNetwork(const Map &map) {
    maxid = 1000000;
    for (auto node: init_network.getNodes()) {
        addIdleEdges(node.second);
    }

    for (auto edge: init_network.getGraph()) {
        createTimestep(edge.start, edge.end);
    }

    addSuperSource(map.start_x, map.start_y);
    addSuperSink(map.finish_x, map.finish_y);
}

void TimeExpandedNetwork::addSuperSource(std::vector<int> start_x, std::vector<int> start_y) {
    int init_super_source = init_network.translateCoord(Network::source.first, Network::source.second);
    int super_source = translateCoord(init_super_source, 0);
    source = super_source;
    for (size_t i = 0; i < start_x.size(); ++i) {
        int init_network_source_id = init_network.translateCoord(start_x[i], start_y[i]);
        int network_source_id = translateCoord(init_network_source_id, 0);
        addEdge(source, network_source_id, 1, 0);
    }
}

void TimeExpandedNetwork::addSuperSink(std::vector<int> finish_x, std::vector<int> finish_y) {
    int init_super_sink = init_network.translateCoord(Network::sink.first, Network::sink.second);
    int super_sink = translateCoord(init_super_sink, 0);
    sink = super_sink;
    for (size_t i = 0; i < finish_x.size(); ++i) {
        int init_network_sink_id = init_network.translateCoord(finish_x[i], finish_y[i]);
        int network_sink_id = translateCoord(init_network_sink_id, 2 * time + 1);
        addEdge(network_sink_id, sink, 1, 0);
    }
}

void TimeExpandedNetwork::addEdge(int start, int end, int capacity, int cost) {
    graph.emplace_back(Edge(start, end, 0, capacity, cost));
    maxid = std::max(maxid, start);
    maxid = std::max(maxid, end);
}

int TimeExpandedNetwork::translateCoord(int _id, int _time) {
    if (time_translations.contains({_id, _time})) {
        return time_translations[{_id, _time}];
    } else {
        time_translations[{_id, _time}] = static_cast<int>(time_translations.size());
        node_reverse_translations[time_translations[{_id, _time}]] = {_id, _time};
        return time_translations[{_id, _time}];
    }
}

void TimeExpandedNetwork::createTimestep(int a, int b) {
    for (int timestep = 1; timestep <= 2 * time; timestep += 2) {
        int a_time_step = translateCoord(a, timestep);
        int a_next_time_step = translateCoord(a, timestep + 1);
        int b_time_step = translateCoord(b, timestep);
        int b_next_time_step = translateCoord(b, timestep + 1);
        int outgoing_fictive_node = translateOutgoingFictiveNode(a_time_step, b_time_step, timestep);
        int incoming_fictive_node = translateIncomingFictiveNode(a_next_time_step, b_next_time_step, timestep + 1);
        addEdge(a_time_step, outgoing_fictive_node, 1, 0);
        addEdge(b_time_step, outgoing_fictive_node, 1, 0);
        addEdge(incoming_fictive_node, a_next_time_step, 1, 0);
        addEdge(incoming_fictive_node, b_next_time_step, 1, 0);
        addEdge(outgoing_fictive_node, incoming_fictive_node, 1, 1);
    }
}

int TimeExpandedNetwork::translateOutgoingFictiveNode(int a, int b, int timestep) {
    outgoing_fictive_nodes[{a, b}] = static_cast<int>(time_translations.size());
    outgoing_nodes_reverse_translations[outgoing_fictive_nodes[{a, b}]] = {a, b};
    return translateCoord(outgoing_fictive_nodes[{a, b}], timestep);
}

int TimeExpandedNetwork::translateIncomingFictiveNode(int a, int b, int timestep) {
    incoming_fictive_nodes[{a, b}] = static_cast<int>(time_translations.size());
    incoming_nodes_reverse_translations[incoming_fictive_nodes[{a, b}]] = {a, b};
    return translateCoord(incoming_fictive_nodes[{a, b}], timestep);
}

void TimeExpandedNetwork::addIdleEdges(int _node) {
    for (int timestep = 1; timestep <= 2 * time + 1; ++timestep) {
        int node_prev_timestep = translateCoord(_node, timestep - 1);
        int node_timestep = translateCoord(_node, timestep);
        if((timestep-1)%2){
            addEdge(node_prev_timestep, node_timestep, 1, holdover_edge_cost);
        }
        else{
            addEdge(node_prev_timestep, node_timestep, 1, 0);
        }
    }
}

int TimeExpandedNetwork::getSource() {
    return source;
}

int TimeExpandedNetwork::getSink() {
    return sink;
}

std::vector<Edge> TimeExpandedNetwork::getEdges() {
    return graph;
}

std::pair<std::pair<int, int>, int> TimeExpandedNetwork::retrieveEdge(int from, int to) {
    if (incoming_nodes_reverse_translations.contains(from) || incoming_nodes_reverse_translations.contains(to)) {
        return {{-1, -1}, -1};
    }
    if (from == source || to == sink) {
        return {{-1, -1}, -1};
    }
    if ((node_reverse_translations[from].second & 1) == 0) {
        return {{-1, -1}, -1};
    }
    if (outgoing_nodes_reverse_translations.contains(to)) {
        int real_to_timestep = outgoing_nodes_reverse_translations[to].first +
                               outgoing_nodes_reverse_translations[to].second - from;
        std::pair<int, int> real_network_nodes = {node_reverse_translations[from].first,
                                                  node_reverse_translations[real_to_timestep].first};
        return {real_network_nodes, node_reverse_translations[from].second};
    } else {
        return {{node_reverse_translations[from].first, node_reverse_translations[from].first},
                node_reverse_translations[from].second};
    }
}

int TimeExpandedNetwork::getTime() {
    return time;
}

SearchResult TimeExpandedNetwork::convertPath(const std::vector<int> &path) {
    int pathlen = 0;
    std::pair<int, int> start = init_network.convertEdge(path[0]);
    std::pair<int, int> goal = init_network.convertEdge(path.back());
    for (int i = 1; i < path.size(); ++i) {
        if (path[i - 1] != path[i]) {
            ++pathlen;
        }
    }
    std::vector<std::pair<int, int>> real_path;
    for (auto node: path) {
        real_path.push_back(init_network.convertEdge(node));
    }
    return SearchResult(start.first, start.second, goal.first, goal.second, pathlen, real_path);
}

int TimeExpandedNetwork::getMaxEdgeId() {
    return maxid;
}



