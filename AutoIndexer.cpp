//
// Created by jadon on 9/15/2021.
//

#include "AutoIndexer.h"
#include <fstream>
#include <iostream>

using namespace std;

// the function reads in from file and stores all lines between two
//pages as one long string - a "paragraph"
void AutoIndexer::readIn(char *arg) {

    ifstream infs(arg);
    if (infs.fail()) {
        cout << "Problem opening file!" << endl;
    }
    else { cout << "File opened successfully!" << endl; }

    char* buffer = new char[1000];
    infs.getline(buffer, 1000, '\n');
    line = buffer;
    while (!infs.eof()) {
        //if there exists an open angle bracket, substring page number
        if (line.find_first('<') != -1) {
            if (line.find_first('-') != -1) {break;} //if end of file <-1>
            page_num = get_pagenum(line);
        }
        infs.getline(buffer, 1000, '\n');
        line = buffer;

        // if no angle bracket found, concatenate line to paragraph
        while (line.find_first('<') == -1) {
            line = line.to_lower();
            paragraph = paragraph + line;
            infs.getline(buffer, 1000,'\n');
            line = buffer;
        }

        Wrapper a(paragraph, page_num);
        para_vector.push_back(a);
        //re-instantiating paragraph acts in place of clear() function
        DSString para;
        paragraph = para;
    }
    delete[] buffer;
    get_phrase();
}

//function substrings page number between two angle brackets
DSString AutoIndexer::get_pagenum(const DSString& line) {
    open_angle = line.find_first('<');
    closed_angle = line.find_first('>');
    return line.substring(open_angle + 1, closed_angle - (open_angle + 1));
}

//function substrings key terms/phrases btwn
// brackets and populates index map
void AutoIndexer::get_phrase() {
    DSString character;
    DSString buffer;
    DSVector<DSString> buff;
    for (auto& itr: para_vector) {
        paragraph = itr.get_phrase();
        int i = paragraph.find_first('[');

        //j instantiated as character after found open bracket
        for (int j = i + 1; j < paragraph.length(); ++j) {
            //when we reach a closing bracket
            if (paragraph.at(j) == ']') {

                //checks to see if phrase already exists in the index
                auto it = book_index.find(phrase1);
                if (it == book_index.end()) {
                    page_vector.push_back(itr.get_pagenum());
                    book_index[phrase1] = page_vector;
                }
                else {
                    //checks to see if that page number has already
                    // been indexed for that word
                    int hold = book_index[phrase1].find(itr.get_pagenum());
                    if (hold == -1) {
                        book_index[phrase1].push_back(itr.get_pagenum());
                    }
                }

                // re-instantiating phrase and vector
                // acts in place of clear() function
                page_vector = buff;
                phrase1 = buffer;

                //checks to see if there's another bracketed phrase
                // within that "page"/paragraph and jumps to it if it exists
                int k = paragraph.find(j, '[');
                if (k == -1) {
                    break;
                }
                else {
                    j = k;
                    continue;
                }
            } //end of if

            //concatenates individual letters to phrase until
            // program runs into a bracket
            if (paragraph.at(j) != '[') {
                character = paragraph.at(j);
                phrase1 = phrase1 + character;
            }

            if (paragraph.at(j) == '[') {
                // nested loop substrings nested terms
                for (int k = j + 1; k < paragraph.length(); ++k) {
                    if (paragraph.at(k) == '[') {continue;}
                    if (paragraph.at(k) != ']') {
                        character = paragraph.at(k);
                        phrase1 = phrase1 + character;
                        phrase2 = phrase2 + character;
                    }
                    if (paragraph.at(k) == ']') {

                        auto it = book_index.find(phrase2);
                        if (it == book_index.end()) {
                            page_vector.push_back(itr.get_pagenum());
                            book_index[phrase2] = page_vector;
                        }
                        else {
                            int hold = book_index[phrase2].find(itr.get_pagenum());
                            if (hold == -1) {
                                book_index[phrase2].push_back(itr.get_pagenum());
                            }
                        }

                        page_vector = buff;
                        phrase2 = buffer;
                        j = k;
                        break;
                    }
                }
            }
        } // end of page/paragraph element traversing
    } //end of paragraph vector/"textbook"
} //end of function

void AutoIndexer::print(char* arg) {
//    for (auto& itr: para_vector) {
//        cout << itr.get_pagenum() << endl;
//        cout << itr.get_phrase() << endl;
//    }

    char hold_char;
    for (auto& itr: book_index) {
        if(itr.first[0] != hold_char) {
            hold_char = itr.first[0];
            if ((hold_char >= 'a') && (hold_char <= 'z')) {
                cout << '[' << static_cast<char>(hold_char - 32) << ']' << endl;
            }
            else {
                cout << '[' << hold_char << ']' << endl;
            }
        }

        cout << itr.first << ": ";
        auto& buff = itr.second;
        int i;
        for (i = 0; i < buff.the_size() - 1; i++) {
            cout << buff.at(i) << ", ";
        }
        i = buff.the_size() - 1;
        cout << buff.at(i) << endl;
    }

    ofstream ofs(arg);
    for (auto& itr: book_index) {
        if(itr.first[0] != hold_char) {
            hold_char = itr.first[0];
            if ((hold_char >= 'a') && (hold_char <= 'z')) {
                ofs << '[' << static_cast<char>(hold_char - 32) << ']' << endl;
            }
            else {
                ofs << '[' << hold_char << ']' << endl;
            }
        }

        ofs << itr.first << ": ";
        auto& buff = itr.second;
        int i;
        for (i = 0; i < buff.the_size() - 1; i++) {
            ofs << buff.at(i) << ", ";
        }
        i = buff.the_size() - 1;
        ofs << buff.at(i) << endl;
    }
}