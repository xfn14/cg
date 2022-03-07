#include "parser.h"

int parseXML(string file) {
    XMLDocument doc;
    if(!doc.LoadFile((XML_PATH + file).c_str())){
        
        return 1;
    }
    return 0;
}

