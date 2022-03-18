#ifndef ANONYMOUSMAPF_MAP_H
#define ANONYMOUSMAPF_MAP_H
#include <vector>

class Map {
public:
    Map();

    ~Map();

    bool loadMap(const char *FileName);

    bool CellIsTraversable(int i, int j) const;

    bool CellOnGrid(int i, int j) const;

    bool CellIsObstacle(int i, int j) const;

    int getValue(int i, int j) const;

    int getMapHeight() const;

    int getMapWidth() const;

    int agents_count;
    std::vector<int> start_x, start_y, finish_x, finish_y;

private:
    int height, width;
    int **Grid;


};

#endif //ANONYMOUSMAPF_MAP_H
