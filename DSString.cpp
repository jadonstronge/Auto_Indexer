//
// Created by jadon on 6/2/2021.
//
// hash function reference:
// https://stackoverflow.com/questions/8317508/hash-function-for-a-string
//

#include "DSString.h"
#include <cstring>
#include <iostream>
using namespace std;


// default constructor creates character array object w/ only null termination
DSString::DSString() {
    str = new char[1];
    str[0] = '\0';
}

// one argument constructor receives string literal,
// instantiates private variable with array length of string literal + 1,
// and copies characters of string literal to private variable
DSString::DSString(const char* arg) {
    str = new char[strlen(arg) + 1];
    strcpy(str, arg);
}

// copy constructor receives DSString object,
// instantiate private variable with array length of object + 1,
// and copies the character of object to private variable
DSString::DSString(const DSString &arg) {
    str = new char[strlen(arg.str) + 1];
    strcpy(str, arg.str);
}

// Destructor
DSString::~DSString() {
    delete[] str;
}

// overloaded assignment operators
DSString& DSString::operator=(const char arg) {
    delete[] str;
    str = new char[2];
    str[0] = arg; str[1] = '\0';
    return *this;
}
DSString& DSString::operator=(const char* arg) {
    delete[] str;
    str = new char[strlen(arg) + 1];
    strcpy(str, arg);
    return *this;
}
DSString& DSString::operator=(const DSString &arg) {
    if (this != &arg) {
        delete[] str;
        str = new char[strlen(arg.str) + 1];
        strcpy(str, arg.str);
        return *this;
    }
    return *this;
}

// overloaded string concatenation
DSString& DSString::operator+(const DSString& arg) {
    static DSString temp;
    temp.str = new char[length() + strlen(arg.str) + 1];
    strcpy(temp.str, str);
    strcat(temp.str, arg.str);
    return temp;
}
DSString& DSString::operator+(const char* arg) {
    static DSString temp;
    temp.str = new char[length() + strlen(arg) + 1];
    strcpy(temp.str, str);
    strcat(temp.str, arg);
    return temp;
}

// overloaded boolean operators (equality of character arrays)
bool DSString::operator==(const char * arg) const {
    int temp = strcmp(str, arg);
    if (temp == 0) {
        return true;
    }
    else { return false; }
}
bool DSString::operator==(const DSString & arg) const {
    int temp = strcmp(str, arg.str);
    if (temp == 0) {
        return true;
    }
    else { return false; }
}

bool DSString::operator> (const char* arg) const {
    int temp = strcmp(str, arg);
    if (temp > 0) {
        return true;
    }
    else { return false; }
}
bool DSString::operator> (const DSString& arg) const {
    int temp = strcmp(str, arg.str);
    if (temp > 0) {
        return true;
    }
    else { return false; }
}


bool DSString::operator<(const char* arg) const {
    int temp = strcmp(str, arg);
    if (temp < 0) {
        return true;
    }
    else { return false; }
}
bool DSString::operator<(const DSString& arg) const {
    int temp = strcmp(str, arg.str);
    if (temp < 0) {
        return true;
    }
    else { return false; }
}

//return character at location in string
char& DSString::operator[](const int index) const {
    return str[index];
}
char& DSString::at(const int index) const {
    return str[index];
}

// returns number of characters (including yt space) in string
int DSString::length() const{
    return strlen(str);
}

// returns tokenized string from longer string
// grabs x amount of chars starting from index
DSString& DSString::substring(int start, int numChars) const{
    static DSString a;
    a.str = new char[numChars + 1];
    for (int i = 0; i < numChars; i++) {
        a.str[i] = str[start];
        start++;
    }
    a.str[numChars] = '\0';
    return a;
}

// overloaded insertion operator
ostream& operator<< (std::ostream& out, const DSString& arg) {
    out << arg.str;
    return out;
}

// returns data of DSString object
char* DSString::c_str() {
    return str;
}

// returns index of first occurrence of a character
int DSString::find_first(const char arg) const {
    for (int i = 0; i < length(); i++) {
        if (str[i] == arg) {
            return i;
        }
    }
    return -1;
}
// returns index of last occurrence of a character
int DSString::find_last(const char arg) const {
    int found;
    for (int i = 0; i < length(); i++) {
        if (str[i] == arg) {
            found = i;
        }
    }
    return found;
}

//finds a character after a specified index
int DSString::find(int index, const char arg) const {
    for (int i = index; i < length(); i++) {
        if (str[i] == arg) {
            return i;
        }
    }
    return -1;
}

// returns a pointer to the first occurrence
// of a substring ("phrase" or "term") in a char array
const char* DSString::find(const DSString& arg) const{
    char* output;
    output = strstr(str, arg.str);
    return output;
}
const char* DSString::find(const char* arg) const{
    char *output;
    output = strstr(str, arg);
    return output;
}

// returns a DSString with all characters set to lower case
DSString& DSString::to_lower() {
    static DSString temp;
    temp.str = new char[length() + 1];
    for (int i = 0; i < length(); ++i) {
        if ((str[i] >= 'A') && (str[i] <= 'Z')) {
            temp.str[i] = static_cast<char>(str[i] + 32);
        }
        else {
            temp.str[i] = str[i];
        }
    }
    temp.str[length()] = '\0';
    return temp;
}

//hashes DSString to create custom index
int DSString::hash() const{
int A = 54059; /* a prime */
int B = 76963; /* another prime */
int C = 86969; /* yet another prime */
int D = 37; /* also prime */
        int h = D;
        for (int i = 0; i < strlen(str); i++) {
            h = (h * A) ^ (str[0] * B);
        }
        return h % C;
}