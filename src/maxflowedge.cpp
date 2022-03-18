#include "maxflowedge.h"

MaxFlowEdge::MaxFlowEdge()
    : from(0)
    , to(0)
    , f(0)
    , c(0)
{
}

MaxFlowEdge::MaxFlowEdge(int _from, int _to, int _f, int _c)
    : from(_from)
    , to(_to)
    , f(_f)
    , c(_c)
{
}
