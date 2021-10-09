//
// Created by jadon on 9/15/2021.
//

#ifndef INC_21F_PA02_AUTOINDEXER_H
#define INC_21F_PA02_AUTOINDEXER_H
#include "Wrapper.h"
#include "DSVector.h"
#include <map>

class AutoIndexer {

private:
    DSString line;
    DSString paragraph;
    DSString page_num; //stores page number
    DSString phrase1, phrase2; //bracketed term/phrases

    int open_angle, closed_angle; //angle brackets

    DSVector<Wrapper> para_vector; //stores all text between pages as paragraph
    DSVector<DSString> page_vector; //vector of page numbers for each phrase
    std::map<DSString, DSVector<DSString>> book_index; //stores the entire index

public:
    AutoIndexer() = default;

    void readIn(char* arg);
    DSString get_pagenum(const DSString&);
    void get_phrase();

    void print(char*);
};


#endif //INC_21F_PA02_AUTOINDEXER_H
