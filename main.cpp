#include <iostream>
#include <map>
#include <chrono>
#include <random>
#include "src/map.h"
#include "src/anonymousMAPF.h"
#include "src/xmllogger.h"
#include "src/xmltags.h"

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cout<<"Error! Pathfinding task file (XML) is not specified!"<<std::endl;
        return 0;
    }
    auto startTime = std::chrono::system_clock::now();
    Map map;
    map.loadMap(argv[1]);
    AnonymousMAPFSolver alg;
    auto res = alg.search(map);
    if(!res.empty()){
        std::cout << "Success" << '\n';
        XmlLogger logger(argv[2]);
        logger.getLog(argv[1]);
        logger.writeToLogPaths(res);
        logger.saveLog();
    }
    auto endTime = std::chrono::system_clock::now();
    std::cout << "Took time: " << std::chrono::duration<double>(endTime-startTime).count() << " seconds \n";
    return 0;
}
