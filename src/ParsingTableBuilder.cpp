//
// Created by Salama on 6/5/2021.
//

#include <set>
#include <map>
#include "../def/ParsingTableBuilder.h"


void ParsingTableBuilder::extract_first() {
    std::unordered_set<std::string> visited;
    // first(terminal) ={terminal}
    for (auto &token:is_terminal) {
        if (token.second) {
            std::set<std::pair<std::vector<std::string>, std::string >> v;
            std::vector<std::string> terminal;
            terminal.push_back(token.first);
            v.insert({terminal, token.first});
            first.insert({token.first, v});
            visited.insert(token.first);
        }
    }

    std::set<std::pair<std::vector<std::string>, std::string >> v;
    v.insert({{epsilon}, epsilon});
    first.insert({epsilon, v});
    for (std::pair<std::string, std::vector<std::vector<std::string>>> production: productions) {
        std::set<std::pair<std::vector<std::string>, std::string >> temp;
        extract_first_recusively(production.first, visited);
    }
    first.erase(epsilon);
}

std::set<std::pair<std::vector<std::string>, std::string >> ParsingTableBuilder
::extract_first_recusively(const std::string &lhs_non_terminal, std::unordered_set<std::string> &visited) {
    std::cout << "zeft" << std::endl;
    if (visited.count(lhs_non_terminal)) {
        return first[lhs_non_terminal];
    }
//    if(is_terminal[lhs_non_terminal])
//    {
//        visited.insert(lhs_non_terminal);
//        return first[lhs_non_terminal];
//    }
    visited.insert(lhs_non_terminal);
    for (const std::vector<std::string> &y: productions[lhs_non_terminal]) {
        int i = 0;
        for (const std::string &str: y) {
            std::set<std::pair<std::vector<std::string>, std::string >> result_set = extract_first_recusively(str,
                                                                                                              visited);
            std::set<std::pair<std::vector<std::string>, std::string >> temp;

            for (std::pair<std::vector<std::string>, std::string> it : result_set) {
                temp.insert({y, it.second});
            }
            result_set = temp;

            first[lhs_non_terminal].insert(result_set.begin(), result_set.end());
            bool is_epsilon_exist = false;
            for (const auto &it : result_set) {
                if (it.second == epsilon) {
                    is_epsilon_exist = true;
                }
            }
            if (!is_epsilon_exist)
                break;
            i++;
        }
        if (i == y.size()) {
            first[lhs_non_terminal].insert({y, epsilon});
        }
    }
    return first[lhs_non_terminal];
}

void ParsingTableBuilder::extract_follow() {
//    If S is the start symbol: $ is in FOLLOW(S)
    follow[starting_symbol].insert("$");
//    if A  aBb is a production rule: everything in FIRST(b) is FOLLOW(B) except e
    for (std::pair<std::string, std::vector<std::vector<std::string>>> production : productions) {
        for (std::vector<std::string> rule: production.second) {
            std::set<std::pair<std::vector<std::string>, std::string >>
                    first_of_next = first[rule[(int) rule.size() - 1]];
            for (int i = (int) rule.size() - 2; i >= 0; i--) {
                std::string previous_token = rule[i];
                std::unordered_set<std::string> next_begin_tokens;
                for (auto it : first_of_next) {
                    next_begin_tokens.insert(it.second);
                }
                follow[previous_token].insert(next_begin_tokens.begin(), next_begin_tokens.end());
                follow[previous_token].erase(epsilon);
            }
        }
    }
//    if A  aB is a production rule or A  aBb is a production rule and e is in First(b):
//      everything in FOLLOW(A) is FOLLOW(B)
    while (true) {
        bool changed = false;
        for (std::pair<std::string, std::vector<std::vector<std::string>>> production : productions) {
            std::string lhs_non_terminal = production.first;
            for (const std::vector<std::string> &rule: production.second) {
                int n = (int) rule.size() - 1;
                std::string s;
                do {
                    s = rule[n--];
                    int original_size = (int) follow[s].size();
                    follow[s].insert(follow[lhs_non_terminal].begin(), follow[lhs_non_terminal].end());
                    changed |= (original_size != (int) follow[s].size());

                } while (n >= 0 && have_epsilon(first[s]));
            }
        }
        if (!changed) break;
    }
}

bool ParsingTableBuilder::have_epsilon(std::set<std::pair<std::vector<std::string>, std::string >> &tokens) {
    for (auto &it : tokens) {
        if (it.second == epsilon) {
            return true;
        }
    }
    return false;
}

std::string ParsingTableBuilder::get_last_non_terminal(int &index, std::vector<std::string> vector) {
    std::string res;
    if (index < 0) {
        return res;
    }
    std::string current = vector[index];
    if (is_terminal[current]) {
        return res;
    } else if (index == vector.size() - 1 || have_epsilon(first[vector[index + 1]])) {
        res = current;
    }
    index--;
    return res;
}

void ParsingTableBuilder::run_extract_table() {
    table.clear();
    sync_table.clear();
    std::unordered_map<std::string, std::set<std::pair<std::vector<std::string>, std::string >>> ff;
    for (std::pair<std::string, std::vector<std::vector<std::string>>> it :productions) {
        if (is_terminal[it.first]) {
            continue;
        }
        for (std::pair<std::vector<std::string>, std::string> sec: first[it.first]) {
            std::pair<std::pair<std::string, std::string>, std::vector<std::string>> temp;
            temp.first.first = it.first;
            temp.first.second = sec.second;
            temp.second = sec.first;
            if (table[{it.first, sec.second}].size() != 0) {
                throw "the productions are ambiguous";
            }
            table.insert(temp);
        }
        if (have_epsilon(first[it.first])) {
            for (std::string sec: follow[it.first]) {
                std::pair<std::pair<std::string, std::string>, std::vector<std::string>> temp;
                temp.first.first = it.first;
                temp.first.second = sec;
                temp.second = {epsilon};
                table.insert(temp);
            }
        } else {
            for (std::string sec: follow[it.first]) {
                sync_table[it.first].insert(sec);
            }
        }
    }
}

void ParsingTableBuilder::build() {
    extract_first();
    extract_follow();
    print_first_follow();
    run_extract_table();
}

void ParsingTableBuilder::print_first_follow() {
    std::cout << "non_terminal\t\t\tfirst\t\t\tfollow" << std::endl;
    for (auto &x: first) {
        if (!is_terminal[x.first] && x.first != epsilon) {
            std::string non_terminal = x.first;
            std::cout << x.first + "\t\t\t";
            std::cout << "{ ";
            for (const auto &it : x.second) {
                std::cout << it.second + ", ";
            }
            std::cout << "}\t\t\t";
            std::cout << "{ ";
            for (const auto &it : follow[x.first]) {
                std::cout << it + ", ";
            }
            std::cout << "}" << std::endl;
        }
    }
}



