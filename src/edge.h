#ifndef ANONYMOUSMAPF_EDGE_H
#define ANONYMOUSMAPF_EDGE_H

struct Edge{
    int start, end, flow, capacity, cost;

    Edge(int _start, int _end, int _flow, int _capacity, int _cost);
};
#endif //ANONYMOUSMAPF_EDGE_H
