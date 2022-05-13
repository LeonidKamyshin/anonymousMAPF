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
        std::cout << "Test #" << i << ": " << std::chrono::duration<double>(endTime-startTime).count() << '\n';
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
