#ifndef ANONYMOUSMAPF_XMLTAGS_H
#define ANONYMOUSMAPF_XMLTAGS_H

#define  TAG_ROOT "root"
    #define TAG_MAP "map"
        #define TAG_WIDTH "width"
        #define TAG_HEIGHT "height"
        #define TAG_STX "startx"
        #define TAG_STY "starty"
        #define TAG_FINX "finishx"
        #define TAG_FINY "finishy"
        #define TAG_GRID "grid"
            #define TAG_ROW "row"
    #define TAG_ALG "algorithm"
        #define TAG_MT "objective"
    #define TAG_LOG "log"
        #define TAG_LPLEVEL "lplevel"
        #define TAG_ATTR_AGENT_ID "agent_id"
                #define TAG_NODE "node"
                #define TAG_ATTR_X "x"
                #define TAG_ATTR_Y "y"
                #define TAG_ATTR_NUMBER "number"

#define TAG_MT_AVGTIME  "avg_time"
#define TAG_MT_MAKESPAN  "makespan"
#define TAG_MT_AVGDIST  "avg_distance"

#define TAG_PATHSELECTION     "*"
#define TAG_MATRIXSEPARATOR   ' '
#endif //ANONYMOUSMAPF_XMLTAGS_H
