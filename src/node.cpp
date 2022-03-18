#include "node.h"

Node::Node(int _x, int _y)
    : x(_x)
    , y(_y)
    , F(0)
    , g(0)
    , H(0)
    , prev(nullptr)
{
}
Node::Node(int _x, int _y, double _g, double _H, Node* _prev)
        : x(_x)
        , y(_y)
        , F(_g + _H)
        , g(_g)
        , H(_H)
        , prev(_prev)
{
}
