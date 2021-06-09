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


//typedef map<pair<string, string>, vector<string> > parsing_table;
//typedef map<string, unordered_set<string>> sync_table;

class InputMatcher {
public:

    InputMatcher(map<pair<string, string>, vector<string> > parsing_table,
                 map<string, unordered_set<string>> sync_table, string start) :
            table(parsing_table),
            recover(sync_table), start(start) {

    }

    vector<string> match(vector<string> input);

private:
    vector<string> match_helper(vector<string> input);

    map<pair<string, string>, vector<string> > table;
    map<string, unordered_set<string>> recover;
    string start;

};


#endif //JAVA_COMPILER_PHASE2_INPUTMATCHER_H