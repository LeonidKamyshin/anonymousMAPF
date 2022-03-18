cmake_minimum_required(VERSION 3.16)
project(anonymousMAPF)

set(CMAKE_CXX_STANDARD 20)

add_executable(anonymousMAPF main.cpp src/ilogger.h src/xmllogger.cpp src/xmllogger.h src/searchresult.h src/astar.h src/map.h src/node.h src/node.cpp src/searchresult.cpp src/map.cpp src/searchrequest.cpp src/searchrequest.h src/astar.cpp src/astaroptions.h src/astaroptions.cpp src/xmltags.h src/constraint.h src/constraint.cpp src/constraints.cpp src/constraints.h src/tinyxml2.cpp src/tinyxml2.h     src/anonymousmapf.cpp src/anonymousmapf.h   src/edge.cpp src/edge.h src/network.cpp src/network.h src/timeexpandednetwork.cpp src/timeexpandednetwork.h "src/maxflow.cpp" "src/maxflow.h" src/maxflowedge.cpp src/maxflowedge.h)
