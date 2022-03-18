#include <iostream>
#include <math.h>
#include "astar.h"
#include "searchrequest.h"

bool Compare(Node* a, Node* b) {
    return std::tie(a->F, a->x, a->y) < std::tie(b->F, b->x, b->y);
};

AStar::AStar(AStarOptions _options)
        : options(_options)
        , CLOSE()
        , OPENED()
        , OPEN(Compare)
{
}

AStar::~AStar() {
    for(auto node:need_to_delete){
        delete node;
    }
}

SearchResult AStar::findPath(const Map &map, const SearchRequest& request)
{
    Node* finish_node;
    Node* start_node = new Node(request.start_x, request.start_y);
    start_node->H = calculateH(start_node, request);
    start_node->F = start_node->H + start_node->g;
    CLOSE[{request.start_x, request.start_y}] = start_node;
    need_to_delete.push_back(start_node);
    OPEN.insert(start_node);
    bool path_found = false;
    while(!OPEN.empty()){
        Node* cur_node = *OPEN.begin();
        OPEN.erase(cur_node);
        OPENED[{cur_node->x, cur_node->y}] = nullptr;
        if(cur_node->x == request.finish_x && cur_node->y == request.finish_y){
            finish_node = cur_node;
            path_found = true;
            break;
        }
        CLOSE[{cur_node->x, cur_node->y}] = cur_node;
        auto sucessors = getSucessors(map, cur_node, request);
        for(auto node:sucessors){
            need_to_delete.push_back(node);
            Node* try_to_find = nullptr;

            if(CLOSE.contains(std::make_pair(node->x, node->y))){
                continue;
            }

            try_to_find = node;
            if(!OPENED[std::make_pair(node->x, node->y)]){
                OPEN.insert(try_to_find);
                OPENED[std::make_pair(node->x, node->y)] = try_to_find;
            }
            else{
                try_to_find = OPENED[std::make_pair(node->x, node->y)];
                OPEN.erase(try_to_find);
                if(node->g < try_to_find->g){
                    try_to_find->prev = cur_node;
                    try_to_find->g = node->g;
                    try_to_find->F = node->F;
                }
                OPEN.insert(try_to_find);
            }
        }
    }

    if (path_found){
        std::vector<std::pair<int, int>> path;
        auto cur_node = finish_node;
        while(cur_node){
            path.emplace_back(cur_node->x, cur_node->y);
            cur_node = cur_node->prev;
        }
        std::reverse(path.begin(), path.end());

        return {request.start_x, request.start_y, request.finish_x, request.finish_y, finish_node->g, path};
    }
    else{
        return {};
    }
}

std::vector<Node*> AStar::getSucessors(const Map& map, Node* node, const SearchRequest& request){
    std::vector<Node*> sucessors;
    int curX = node->x;
    int curY = node->y;
    for(int i = -1; i <=1; ++i){
        for(int j = -1; j <= 1; ++j){
            curX += i;
            curY += j;
            if(canMoveTo(map, node, i, j)){
                Node* curNode = new Node(curX, curY);
                curNode->prev = node;
                curNode->g = node->g + std::sqrt(i*i + j*j);
                curNode->H = calculateH(curNode, request);
                curNode->F = curNode->H + curNode->g;
                sucessors.push_back(curNode);
            }
            curX-= i;
            curY-=j;
        }
    }
    return sucessors;
}

bool AStar::canMoveTo(const Map& map, Node* node, int dx, int dy){
    if(dx == 0 && dy == 0){
        return false;
    }

    bool canMoveTo = map.CellOnGrid(node->x + dx, node->y + dy) && map.CellIsTraversable(node->x + dx, node->y + dy);
    if(dx == 0 || dy == 0){
        return canMoveTo;
    }
    else{
        return false;
    }
}

double AStar::calculateH(const Node* node, const SearchRequest& request){
    int dx = node->x - request.finish_x;
    int dy = node->y - request.finish_y;
    switch(options.METRIC_TYPE){
        case MetricType::DiagonalDistance:
            return std::abs(dx - dy) + std::sqrt(2)*std::min(dx,dy);
        case MetricType::Manhattan:
            return std::abs(dx) + std::abs(dy);
        case MetricType::Euclidean:
            return std::sqrt(dx*dx + dy*dy);
        case MetricType::Chebyshev:
            return std::max(std::abs(dx), std::abs(dy));

    }
}