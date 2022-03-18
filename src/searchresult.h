#ifndef ANONYMOUSMAPF_SEARCHRESULT_H
#define ANONYMOUSMAPF_SEARCHRESULT_H
#include <vector>

struct SearchResult{
    bool path_exists;
    int start_x, start_y, finish_x, finish_y, time;
    double pathlen;
    std::vector<std::pair<int,int>> path;

    SearchResult();

    SearchResult(int _start_x, int _start_y, int _finish_x, int _finish_y, double _pathlen,
                 std::vector<std::pair<int,int>> path);


};
#endif //ANONYMOUSMAPF_SEARCHRESULT_H
