#include <utility>
#include <vector>

#include "searchresult.h"

SearchResult::SearchResult(int _start_x, int _start_y, int _finish_x, int _finish_y, double _pathlen,
                           std::vector<std::pair<int,int>> _path)
    : path_exists(true)
    , start_x(_start_x)
    , start_y(_start_y)
    , finish_x(_finish_x)
    , finish_y(_finish_y)
    , pathlen(_pathlen)
    , path(std::move(_path))
    , time(static_cast<int>(_path.size()))
{
}

SearchResult::SearchResult()
        : path_exists(true)
        , start_x()
        , start_y()
        , finish_x()
        , finish_y()
        , pathlen()
        , path()
        , time()
{
}