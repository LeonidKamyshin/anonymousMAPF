#ifndef ANONYMOUSMAPF_NODE_H
#define ANONYMOUSMAPF_NODE_H

struct Node{
    const int x, y;
    double F, g, H;
    Node* prev;

    Node(int _x, int _y);
    Node(int _x, int _y, double _g, double _H, Node* _parent);
};
#endif //ANONYMOUSMAPF_NODE_H
