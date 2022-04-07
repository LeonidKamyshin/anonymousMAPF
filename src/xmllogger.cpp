#include "xmllogger.h"
#include "xmltags.h"
#include "searchresult.h"

#include <iostream>

using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

XmlLogger::XmlLogger(std::string _LogFileName)
    : LogFileName(_LogFileName)
{
}

bool XmlLogger::getLog(const char *FileName)
{
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

void XmlLogger::saveLog()
{
    doc.SaveFile(LogFileName.c_str());
}

void XmlLogger::writeToLogPaths(const std::vector<SearchResult> &paths)
{
    XMLElement *logTag = doc.FirstChildElement(TAG_ROOT);
    logTag = logTag->FirstChildElement(TAG_LOG);

    for(int64_t i = 0; i < paths.size(); ++i){
        XMLElement *element = doc.NewElement(TAG_LPLEVEL);
        element->SetAttribute(TAG_ATTR_AGENT_ID, i+1);
        for(int j = 0; j < paths[i].path.size(); ++j){
            XMLElement *cur_element = doc.NewElement(TAG_NODE);
            cur_element->SetAttribute(TAG_ATTR_X, static_cast<int64_t>(paths[i].path[j].first));
            cur_element->SetAttribute(TAG_ATTR_Y, static_cast<int64_t>(paths[i].path[j].second));
            cur_element->SetAttribute(TAG_ATTR_NUMBER, static_cast<int64_t>(j));
            element->InsertEndChild(cur_element);
        }
        logTag->InsertEndChild(element);
    }
}

void XmlLogger::writeToLogNotFound()
{
//    XMLElement *node = doc.FirstChildElement(TAG_ROOT)->FirstChildElement(TAG_LOG)->FirstChildElement(TAG_PATH);
//    node->InsertEndChild(doc.NewText("Path NOT found!"));
}

