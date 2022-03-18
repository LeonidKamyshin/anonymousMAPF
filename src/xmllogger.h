#ifndef XMLLOGGER_H
#define	XMLLOGGER_H
#include "tinyxml2.h"
#include "ilogger.h"
#include "searchresult.h"


//That's the class that flushes the data to the output XML


class XmlLogger {

public:
    XmlLogger(std::string LogFileName);

    ~XmlLogger() {};

    bool getLog(const char *FileName);

    void saveLog();

    void writeToLogPaths(const std::vector<SearchResult> &paths);

    void writeToLogNotFound();

private:
    std::string LogFileName;
    tinyxml2::XMLDocument doc;
};

#endif

