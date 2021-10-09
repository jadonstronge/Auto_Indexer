//
// Created by jadon on 9/15/2021.
//

#ifndef INC_21F_PA02_WRAPPER_H
#define INC_21F_PA02_WRAPPER_H

#include "DSString.h"
#include "DSVector.h"
class Wrapper {

private:
    DSVector<DSString> page_vector;
    DSString page_num;
    DSString phrase;

public:
    Wrapper() = default;
    Wrapper(const DSString&, const DSString&);
    Wrapper(const DSString&, const DSVector<DSString>&);

    bool operator== (const DSString&);

    DSVector<DSString>& get_pagevector();
    void set_pagevector(const DSVector<DSString>&);
    DSString& get_pagenum();
    void set_pagenum(const DSString&);
    DSString& get_phrase();
    void set_phrase(const DSString&);

};


#endif //INC_21F_PA02_WRAPPER_H
