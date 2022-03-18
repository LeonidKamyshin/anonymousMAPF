#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "map.h"
#include "tinyxml2.h"
#include "xmltags.h"
#include <algorithm>

Map::Map()
{
    height = -1;
    width = -1;
    Grid = nullptr;
}

Map::~Map()
{
    if (Grid) {
        for (int i = 0; i < height; ++i)
            delete[] Grid[i];
        delete[] Grid;
    }
}

bool Map::CellIsTraversable(int i, int j) const
{
    return Grid[i][j] == 0;
}

bool Map::CellIsObstacle(int i, int j) const
{
    return Grid[i][j] != 1;
}

bool Map::CellOnGrid(int i, int j) const
{
    return i < height && i >= 0 && j < width && j >= 0;
}

bool Map::loadMap(const char *FileName)
{
    int rowiter = 0, grid_i = 0, grid_j = 0;

    tinyxml2::XMLElement *root = 0, *map = 0, *element = 0, *mapnode;

    std::string value;
    std::stringstream stream;

    bool hasGridMem = false, hasGrid = false, hasHeight = false, hasWidth = false, hasSTX = false, hasSTY = false, hasFINX = false, hasFINY = false, hasCellSize = false;

    tinyxml2::XMLDocument doc;

    // Load XML File
    if (doc.LoadFile(FileName) != tinyxml2::XMLError::XML_SUCCESS) {
        std::cout << "Error opening XML file!" << std::endl;
        return false;
    }

    // Get ROOT element
    root = doc.FirstChildElement(TAG_ROOT);
    if (!root) {
        std::cout << "Error! No '" << TAG_ROOT << "' tag found in XML file!" << std::endl;
        return false;
    }

    // Get MAP element
    map = root->FirstChildElement(TAG_MAP);
    if (!map) {
        std::cout << "Error! No '" << TAG_MAP << "' tag found in XML file!" << std::endl;
        return false;
    }

    for (mapnode = map->FirstChildElement(); mapnode; mapnode = mapnode->NextSiblingElement()) {
        element = mapnode->ToElement();
        value = mapnode->Value();
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);

        stream.str("");
        stream.clear();
        if(value != TAG_GRID)
        {
            stream << element->GetText();
        }
        if (!hasGridMem && hasHeight && hasWidth) {
            Grid = new int *[height];
            for (int i = 0; i < height; ++i)
                Grid[i] = new int[width];
            hasGridMem = true;
        }

        if (value == TAG_HEIGHT) {
            if (hasHeight) {
                std::cout << "Warning! Duplicate '" << TAG_HEIGHT << "' encountered." << std::endl;
                std::cout << "Only first value of '" << TAG_HEIGHT << "' =" << height << "will be used."
                          << std::endl;
            }
            else {
                if (!((stream >> height) && (height > 0))) {
                    std::cout << "Warning! Invalid value of '" << TAG_HEIGHT
                              << "' tag encountered (or could not convert to integer)." << std::endl;
                    std::cout << "Value of '" << TAG_HEIGHT << "' tag should be an integer >=0" << std::endl;
                    std::cout << "Continue reading XML and hope correct value of '" << TAG_HEIGHT
                              << "' tag will be encountered later..." << std::endl;
                }
                else
                    hasHeight = true;
            }
        }
        else if (value == TAG_WIDTH) {
            if (hasWidth) {
                std::cout << "Warning! Duplicate '" << TAG_WIDTH << "' encountered." << std::endl;
                std::cout << "Only first value of '" << TAG_WIDTH << "' =" << width << "will be used." << std::endl;
            }
            else {
                if (!((stream >> width) && (width > 0))) {
                    std::cout << "Warning! Invalid value of '" << TAG_WIDTH
                              << "' tag encountered (or could not convert to integer)." << std::endl;
                    std::cout << "Value of '" << TAG_WIDTH << "' tag should be an integer AND >0" << std::endl;
                    std::cout << "Continue reading XML and hope correct value of '" << TAG_WIDTH
                              << "' tag will be encountered later..." << std::endl;

                }
                else
                    hasWidth = true;
            }
        }
        else if (value == TAG_STX) {
            if (!hasWidth) {
                std::cout << "Error! '" << TAG_STX << "' tag encountered before '" << TAG_WIDTH << "' tag."
                          << std::endl;
                return false;
            }

            if (hasSTX) {
                std::cout << "Warning! Duplicate '" << TAG_STX << "' encountered." << std::endl;
            }
            else {
                int cur_start_x;
                while(stream >> cur_start_x){
                    start_x.push_back(cur_start_x);
                    hasSTX = true;
                }
            }
        }
        else if (value == TAG_STY) {
            if (!hasHeight) {
                std::cout << "Error! '" << TAG_STY << "' tag encountered before '" << TAG_HEIGHT << "' tag."
                          << std::endl;
                return false;
            }

            if (hasSTY) {
                std::cout << "Warning! Duplicate '" << TAG_STY << "' encountered." << std::endl;
            }
            else {
                int cur_start_y;
                while(stream >> cur_start_y){
                    start_y.push_back(cur_start_y);
                    hasSTY = true;
                }
            }
        }
        else if (value == TAG_FINX) {
            if (!hasWidth) {
                std::cout << "Error! '" << TAG_FINX << "' tag encountered before '" << TAG_WIDTH << "' tag."
                          << std::endl;
                return false;
            }

            if (hasFINX) {
                std::cout << "Warning! Duplicate '" << TAG_FINX << "' encountered." << std::endl;
            }
            else {
                int cur_finish_x;
                while(stream >> cur_finish_x){
                    finish_x.push_back(cur_finish_x);
                    hasFINX = true;
                }
            }
        }
        else if (value == TAG_FINY) {
            if (!hasHeight) {
                std::cout << "Error! '" << TAG_FINY << "' tag encountered before '" << TAG_HEIGHT << "' tag."
                          << std::endl;
                return false;
            }

            if (hasFINY) {
                std::cout << "Warning! Duplicate '" << TAG_FINY << "' encountered." << std::endl;
            }
            else {
                int cur_finish_y;
                while(stream >> cur_finish_y){
                    finish_y.push_back(cur_finish_y);
                    hasFINY = true;
                }
            }
        }
        else if (value == TAG_GRID) {
            hasGrid = true;
            if (!(hasHeight && hasWidth)) {
                std::cout << "Error! No '" << TAG_WIDTH << "' tag or '" << TAG_HEIGHT << "' tag before '"
                          << TAG_GRID << "'tag encountered!" << std::endl;
                return false;
            }
            element = mapnode->FirstChildElement();
            while (grid_i < height) {
                if (!element) {
                    std::cout << "Error! Not enough '" << TAG_ROW << "' tags inside '" << TAG_GRID << "' tag."
                              << std::endl;
                    std::cout << "Number of '" << TAG_ROW
                              << "' tags should be equal (or greater) than the value of '" << TAG_HEIGHT
                              << "' tag which is " << height << std::endl;
                    return false;
                }
                std::string str = element->GetText();
                std::vector<std::string> elems;
                std::stringstream ss(str);
                std::string item;
                while (std::getline(ss, item, ' '))
                    elems.push_back(item);
                rowiter = grid_j = 0;
                int val;
                if (elems.size() > 0)
                    for (grid_j = 0; grid_j < width; ++grid_j) {
                        if (grid_j == elems.size())
                            break;
                        stream.str("");
                        stream.clear();
                        stream << elems[grid_j];
                        stream >> val;
                        Grid[grid_i][grid_j] = val;
                    }

                if (grid_j != width) {
                    std::cout << "Invalid value on " << TAG_GRID << " in the " << grid_i + 1 << " " << TAG_ROW
                              << std::endl;
                    return false;
                }
                ++grid_i;

                element = element->NextSiblingElement();
            }
        }
    }
    agents_count = start_x.size();
    //some additional checks
    if (!hasGrid) {
        std::cout << "Error! There is no tag 'grid' in xml-file!\n";
        return false;
    }
    if (!(hasFINX && hasFINY && hasSTX && hasSTY))
        return false;

    if(start_x.size() != start_y.size() || start_x.size() != finish_x.size() || start_x.size() != finish_y.size()){
        std::cout << "Start and finish count does not equal!"
                  << std::endl;
    }
    for(int i = 0; i < start_x.size(); ++i){
        if (Grid[start_x[i]][start_y[i]] != 0) {
            std::cout << "Error! Start cell is not traversable (cell's value is" << Grid[start_x[i]][start_y[i]] << ")!"
                      << std::endl;
            return false;
        }
        if (Grid[finish_x[i]][finish_y[i]] != 0) {
            std::cout << "Error! Goal cell is not traversable (cell's value is" << Grid[finish_x[i]][finish_y[i]] << ")!"
                      << std::endl;
            return false;
        }
    }

    return true;
}



int Map::getValue(int i, int j) const
{
    if (i < 0 || i >= height)
        return -1;

    if (j < 0 || j >= width)
        return -1;

    return Grid[i][j];
}

int Map::getMapHeight() const
{
    return height;
}

int Map::getMapWidth() const
{
    return width;
}
