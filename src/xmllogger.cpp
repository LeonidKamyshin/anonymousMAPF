#include "xmllogger.h"
#include "xmltags.h"
#include "searchresult.h"

#include <iostream>
#include <numeric>

using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

XmlLogger::XmlLogger(std::string _LogFileName)
        : LogFileName(_LogFileName) {
}

bool XmlLogger::getLog(const char *FileName) {
    if (doc.LoadFile(FileName) != tinyxml2::XMLError::XML_SUCCESS) {
        std::cout << "Error opening input XML file" << std::endl;
        return false;
    }

    XMLElement *log, *root = doc.FirstChildElement(TAG_ROOT);

    if (!root) {
        std::cout << "No '" << TAG_ROOT << "' element found in XML file" << std::endl;
        std::cout << "Can not create log" << std::endl;
        return false;
    }

    root->InsertEndChild(doc.NewElement(TAG_LOG));

    return true;
}

void XmlLogger::saveLog() {
    doc.SaveFile(LogFileName.c_str());
}

void XmlLogger::saveLog(const char *FileName){
    doc.SaveFile(FileName);
}

void XmlLogger::writeToLogPaths(const std::vector<SearchResult> &paths) {
    XMLElement *logTag = doc.FirstChildElement(TAG_ROOT);
    logTag = logTag->FirstChildElement(TAG_LOG);

    for (int i = 0; i < paths.size(); ++i) {
        XMLElement *element = doc.NewElement(TAG_LPLEVEL);
        element->SetAttribute(TAG_ATTR_AGENT_ID, i + 1);
        for (int j = 0; j < paths[i].path.size(); ++j) {
            XMLElement *cur_element = doc.NewElement(TAG_NODE);
            cur_element->SetAttribute(TAG_ATTR_X, paths[i].path[j].first);
            cur_element->SetAttribute(TAG_ATTR_Y, paths[i].path[j].second);
            cur_element->SetAttribute(TAG_ATTR_NUMBER, j);
            element->InsertEndChild(cur_element);
        }
        logTag->InsertEndChild(element);
    }
}

void XmlLogger::writeStart(const std::vector<int> &x,
                           const std::vector<int> &y) {
    std::vector<std::string> str_x(x.size()), str_y(y.size());
    std::transform(x.begin(), x.end(), str_x.begin(), [](int a){return std::to_string(a)+" ";});
    std::transform(y.begin(), y.end(), str_y.begin(), [](int a){return std::to_string(a)+" ";});

    XMLElement *tagX = doc.FirstChildElement(TAG_ROOT)->FirstChildElement(TAG_MAP)->FirstChildElement(TAG_STX);
    XMLElement *tagY = doc.FirstChildElement(TAG_ROOT)->FirstChildElement(TAG_MAP)->FirstChildElement(TAG_STY);
    tagX->SetText(std::accumulate(str_x.begin(), str_x.end(), std::string("")).c_str());
    tagY->SetText(std::accumulate(str_y.begin(), str_y.end(), std::string("")).c_str());
}

void XmlLogger::writeFinish(const std::vector<int> &x,
                            const std::vector<int> &y) {
    std::vector<std::string> str_x(x.size()), str_y(y.size());
    std::transform(x.begin(), x.end(), str_x.begin(), [](int a){return std::to_string(a)+" ";});
    std::transform(y.begin(), y.end(), str_y.begin(), [](int a){return std::to_string(a)+" ";});

    XMLElement *tagX = doc.FirstChildElement(TAG_ROOT)->FirstChildElement(TAG_MAP)->FirstChildElement(TAG_FINX);
    XMLElement *tagY = doc.FirstChildElement(TAG_ROOT)->FirstChildElement(TAG_MAP)->FirstChildElement(TAG_FINY);
    tagX->SetText(std::accumulate(str_x.begin(), str_x.end(), std::string("")).c_str());
    tagY->SetText(std::accumulate(str_y.begin(), str_y.end(), std::string("")).c_str());
}

void XmlLogger::writeObjective(const std::string objective){
    XMLElement *tagObjective = doc.FirstChildElement(TAG_ROOT)->FirstChildElement(TAG_ALG)->FirstChildElement(TAG_MT);
    tagObjective->SetText(objective.c_str());
}
