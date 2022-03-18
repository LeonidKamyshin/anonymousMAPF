#ifndef ANONYMOUSMAPF_MAXFLOWEDGE_H
#define ANONYMOUSMAPF_MAXFLOWEDGE_H

struct MaxFlowEdge {
    int from, to, f, c;

    MaxFlowEdge();

    MaxFlowEdge(int _from, int _to, int _f, int _c);
};

#endif //ANONYMOUSMAPF_MAXFLOWEDGE_H
