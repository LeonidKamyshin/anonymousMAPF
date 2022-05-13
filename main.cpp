#include <iostream>
#include <map>
#include <chrono>
#include "src/map.h"
#include "src/anonymousMAPF.h"
#include "src/xmllogger.h"

void testing(){
    for(int i = 1; i <= 80; ++i){
        auto startTime = std::chrono::system_clock::now();
        Map map;
        std::string path ="../tests/" + std::to_string(i) + ".xml";
        map.loadMap(const_cast<char*>(path.c_str()));
        AnonymousMAPFSolver alg;
        auto res = alg.search(map);

        XmlLogger logger("../log1.xml");
        logger.getLog(const_cast<char*>(path.c_str()));
        logger.writeToLogPaths(res);
        logger.saveLog();
        auto endTime = std::chrono::system_clock::now();
        std::cout << "Took time for test " << i << ": " << std::chrono::duration<double>(endTime-startTime).count() << '\n';
    }
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cout<<"Error! Pathfinding task file (XML) is not specified!"<<std::endl;
        return 0;
    }
    auto startTime = std::chrono::system_clock::now();
    Map map;
    map.loadMap(argv[1]);
    for(int i = 0; i < map.getMapHeight(); i++){
        for(int j = 0; j < map.getMapWidth(); ++j){
            std::cout << !map.CellIsTraversable(i, j) << " ";
        }
        std::cout << '\n';
    }
    std::cout << "success" << '\n';
    AnonymousMAPFSolver alg;
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
    auto endTime = std::chrono::system_clock::now();
    std::cout << "Took time: " << std::chrono::duration<double>(endTime-startTime).count() << '\n';
    return 0;
}
