//
// Created by KING on 6/9/2021.
//

#ifndef JAVA_COMPILER_PHASE2_INPUTMATCHER_H
#define JAVA_COMPILER_PHASE2_INPUTMATCHER_H

#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::unordered_set;


class InputMatcher {
public:

    void setTable(map<pair<string, string>, vector<string> > parsing_table,
                  map<string, unordered_set<string>> sync_table, string start);

    vector<string> match(string input);

    static InputMatcher& getInstance(){
        static InputMatcher inputMatcher;
        return inputMatcher;
    }

private:
    InputMatcher(){}
    unordered_set<string> non_terminals;
    map<pair<string, string>, vector<string> > table;
    vector<string> stk;
    map<string, unordered_set<string>> recover;
    string start;



    void fill_non_terminals();
    vector<string> match_one_token(string input);
    bool match_helper(string input, string &log);

};


#endif //JAVA_COMPILER_PHASE2_INPUTMATCHER_H