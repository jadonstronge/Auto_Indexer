//
// Created by jadon on 9/15/2021.
//

#include "Wrapper.h"

//stores paragraph and corresponding page number
Wrapper::Wrapper(const DSString& p, const DSString& num) {
    phrase = p;
    page_num = num;
}
//stores phrase and corresponding page numbers
Wrapper::Wrapper(const DSString& p, const DSVector<DSString>& num) {
    phrase = p;
    page_vector = num;
}

bool Wrapper::operator==(const DSString& arg) {
    return (arg == get_phrase());
}


DSVector<DSString>& Wrapper::get_pagevector() {
    return page_vector;
}
void Wrapper::set_pagevector(const DSVector<DSString> & num) {
    page_vector = num;
}

DSString& Wrapper::get_pagenum() {
    return page_num;
}
void Wrapper::set_pagenum(const DSString & num) {
    page_num = num;
}

DSString& Wrapper::get_phrase() {
    return phrase;
}
void Wrapper::set_phrase(const DSString & p) {
    phrase = p;
}