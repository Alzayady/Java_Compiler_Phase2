//
// Created by Salama on 6/5/2021.
//

#ifndef JAVA_COMPILER_PHASE2_PARSINGTABLEBUILDER_H
#define JAVA_COMPILER_PHASE2_PARSINGTABLEBUILDER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class ParsingTableBuilder {
public:
    ParsingTableBuilder(std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions,
                        std::unordered_map<std::string, bool> isTerminal, std::string startingSymbol)
            : productions(productions), is_terminal(isTerminal), starting_symbol(startingSymbol) {

    }
    void extract_first();
    void extract_follow();
    std::unordered_map<std::string, std::unordered_set<std::string>> get_first()
    {
        return first;
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> get_follow()
    {
        return follow;
    }

private:
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
    std::unordered_map<std::string, bool> is_terminal;
    std::unordered_map<std::string, std::unordered_set<std::string>> first;
    std::unordered_map<std::string, std::unordered_set<std::string>> follow;
    std::string starting_symbol;
    std::string epsilon = "Epsilon";
    std::unordered_set<std::string> extract_first_recusively(const std::string& lhs_non_terminal,
                                                             std::unordered_set<std::string> &visited);
    std::string get_last_non_terminal(int &index, std::vector<std::string> vector);
};

#endif //JAVA_COMPILER_PHASE2_PARSINGTABLEBUILDER_H
