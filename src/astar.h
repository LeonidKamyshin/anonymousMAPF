#ifndef ANONYMOUSMAPF_ASTAR_H
#define ANONYMOUSMAPF_ASTAR_H

#include "searchresult.h"
#include "searchrequest.h"
#include "node.h"
#include "map.h"
#include "astaroptions.h"
#include <list>
#include <functional>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>

class AStar {
public:
    AStar(AStarOptions options);

    ~AStar();

    SearchResult findPath(const Map &map, const SearchRequest& request);

protected:
    std::vector<Node*> getSucessors(const Map& map, Node* node, const SearchRequest& request);
    bool canMoveTo(const Map& map, Node* node, int dx, int dy);
    double calculateH(const Node* node, const SearchRequest& request);

    std::map<std::pair<int,int>, Node*> CLOSE;
    std::map<std::pair<int,int>, Node*> OPENED;
    std::set<Node*, std::function<bool(Node*, Node*)>> OPEN;
    std::vector<Node*> need_to_delete;
    AStarOptions options;
};

#endif //ANONYMOUSMAPF_ASTAR_H
