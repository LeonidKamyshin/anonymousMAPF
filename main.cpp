#include <iostream>
#include <map>
#include "src/map.h"
#include "src/anonymousMAPF.h"
#include "src/xmllogger.h"

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cout<<"Error! Pathfinding task file (XML) is not specified!"<<std::endl;
        return 0;
    }

    Map map;
    map.loadMap(argv[1]);
    for(int i = 0; i < map.getMapHeight(); i++){
        for(int j = 0; j < map.getMapWidth(); ++j){
            std::cout << !map.CellIsTraversable(i, j) << " ";
        }
        std::cout << '\n';
    }
    std::cout << "success" << '\n';
    AnonymousMAPF alg;
    auto res = alg.search(map);
    int index = 0;
    for(auto path:res){
        std::cout << "Index is: " << index << '\n';
        ++index;
        for(auto coord:path.path){
            std::cout << coord.first << " " << coord.second << '\n';
        }
    }
    XmlLogger logger(argv[2]);
    logger.getLog(argv[1]);
    logger.writeToLogPaths(res);
    logger.saveLog();
    return 0;
}
