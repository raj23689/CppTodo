#pragma once
#include <string>
#include <vector>

#define FILELOCATION "/Documents/todo.txt" // at ~/
#define LINESEPARATOR "and"
#define PRINTSERIAL true // print serial number before task description

struct nameValue {
  std::string str;
  int integer;
};

std::vector<nameValue> errorsCaught;
std::string lastInputLine = "";

std::vector<nameValue> dayNameList = {
    // English
    {"First", 1},
    {"Second", 2},
    {"Third", 3},
    {"Fourth", 4},
    {"Fifth", 5},
    {"Sixth", 6},
    {"Seventh", 7},
    {"Eighth", 8},
    {"Ninth", 9},
    {"Tenth", 10},
    {"Eleventh", 11},
    {"Twelfth", 12},
    {"Thirteenth", 13},
    {"Fourteenth", 14},
    {"Fifteenth", 15},
    {"Sixteenth", 16},
    {"Seventeenth", 17},
    {"Eighteenth", 18},
    {"Nineteenth", 19},
    {"Twentieth", 20},
    {"Twenty-first", 21},
    {"Twenty-second", 22},
    {"Twenty-third", 23},
    {"Twenty-fourth", 24},
    {"Twenty-fifth", 25},
    {"Twenty-sixth", 26},
    {"Twenty-seventh", 27},
    {"Twenty-eighth", 28},
    {"Twenty-ninth", 29},
    {"Thirtieth", 30},
    {"Thirty-first", 31},

    {"1.", 1},
    {"2.", 2},
    {"3.", 3},
    {"4.", 4},
    {"5.", 5},
    {"6.", 6},
    {"7.", 7},
    {"8.", 8},
    {"9.", 9},
    {"10.", 10},
    {"11.", 11},
    {"12.", 12},
    {"13.", 13},
    {"14.", 14},
    {"15.", 15},
    {"16.", 16},
    {"17.", 17},
    {"18.", 18},
    {"19.", 19},
    {"20.", 20},
    {"21.", 21},
    {"22.", 22},
    {"23.", 23},
    {"24.", 24},
    {"25.", 25},
    {"26.", 26},
    {"27.", 27},
    {"28.", 28},
    {"29.", 29},
    {"30.", 30},
    {"31.", 31},

};

std::vector<nameValue> monthNameList = {
    // English
    {"january", 1},   {"february", 2}, {"march", 3},     {"april", 4},
    {"may", 5},       {"june", 6},     {"july", 7},      {"august", 8},
    {"september", 9}, {"october", 10}, {"november", 11}, {"december", 12},

    {"jan", 1},       {"feb", 2},      {"febr", 2},      {"mar", 3},
    {"apr", 4},       {"may", 5},      {"jun", 6},       {"jul", 7},
    {"aug", 8},       {"sep", 9},      {"sept", 9},      {"oct", 10},
    {"nov", 11},      {"dec", 12},

};
