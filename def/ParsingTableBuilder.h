//
// Created by Salama on 6/5/2021.
//

#ifndef JAVA_COMPILER_PHASE2_PARSINGTABLEBUILDER_H
#define JAVA_COMPILER_PHASE2_PARSINGTABLEBUILDER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

class ParsingTableBuilder {
public:
    ParsingTableBuilder(std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions,
                        std::unordered_map<std::string, bool> isTerminal, std::string startingSymbol)
            : productions(productions), is_terminal(isTerminal), starting_symbol(startingSymbol) {

    }



    std::unordered_map<std::string, std::set<std::pair<std::vector<std::string>, std::string>>> get_first() {
        return first;
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> get_follow() {
        return follow;
    }

    std::map<std::pair<std::string, std::string>, std::vector<std::string>> get_table() {
        return table;
    }

    std::map<std::string, std::unordered_set<std::string>> get_sync_table() {
        return sync_table;
    }

    void build();
    void run_extract_table();

private:
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
    std::unordered_map<std::string, bool> is_terminal;
    std::unordered_map<std::string, std::set<std::pair<std::vector<std::string>, std::string >>> first;
    //                                                               production    , symbol
    std::unordered_map<std::string, std::unordered_set<std::string>> follow;
    std::string starting_symbol;
    std::string epsilon = "\\L";
    std::map<std::pair<std::string, std::string>, std::vector<std::string>> table;
    std::map<std::string, std::unordered_set<std::string>> sync_table;

    std::set<std::pair<std::vector<std::string>, std::string >>
    extract_first_recusively(const std::string &lhs_non_terminal,
                             std::unordered_set<std::string> &visited);

    std::string get_last_non_terminal(int &index, std::vector<std::string> vector);

    bool have_epsilon(std::set<std::pair<std::vector<std::string>, std::string>> &tokens);
    void extract_first();
    void extract_follow();
    void print_first_follow();

};

#endif //JAVA_COMPILER_PHASE2_PARSINGTABLEBUILDER_H
