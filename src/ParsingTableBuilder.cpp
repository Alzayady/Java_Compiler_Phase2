//
// Created by Salama on 6/5/2021.
//

#include "../def/ParsingTableBuilder.h"


void ParsingTableBuilder::extract_first()
{
    std::unordered_set<std::string> visited;
    // first(terminal) ={terminal}
    for(auto &token:is_terminal)
    {
        if(token.second)
        {
            std::unordered_set<std::string>v;
            v.insert(token.first);
            first.insert({token.first, v});
            visited.insert(token.first);
        }
    }
    std::unordered_set<std::string> v;v.insert(epsilon);
    first.insert({epsilon, v});
    for(std::pair<std::string, std::vector<std::vector<std::string>>> production: productions)
    {
        std::unordered_set<std::string> temp;
            temp = extract_first_recusively(production.first, visited);
            first[production.first] = temp;
    }
    first.erase(epsilon);
}
std::unordered_set<std::string> ParsingTableBuilder::extract_first_recusively(const std::string& lhs_non_terminal,
                                                                              std::unordered_set<std::string> &visited)
{
    if (visited.count(lhs_non_terminal))
    {
        return first[lhs_non_terminal];
    }
//    if(is_terminal[lhs_non_terminal])
//    {
//        visited.insert(lhs_non_terminal);
//        return first[lhs_non_terminal];
//    }
    visited.insert(lhs_non_terminal);
    for(const std::vector<std::string>& y: productions[lhs_non_terminal])
    {
        int i =0;
        for(const std::string& str: y)
        {
            std::unordered_set<std::string> result_set = extract_first_recusively(str, visited);
            first[lhs_non_terminal].insert(result_set.begin(), result_set.end());
            if (!result_set.count(epsilon))
                break;
            i++;
        }
        if(i == y.size())
        {
            first[lhs_non_terminal].insert(epsilon);
        }
    }
    return first[lhs_non_terminal];
}

void ParsingTableBuilder::extract_follow()
{
//    If S is the start symbol: $ is in FOLLOW(S)
    follow[starting_symbol].insert("$");
//    if A  aBb is a production rule: everything in FIRST(b) is FOLLOW(B) except e
        for (std::pair<std::string, std::vector<std::vector<std::string>>> production : productions)
        {
            for (std::vector<std::string> rule: production.second) {
               std::unordered_set<std::string> first_of_next = first[rule[(int)rule.size() - 1]];
                for (int i = (int)rule.size() - 2; i >=0 ; i--) {
                    std::string previous_token = rule[i];
                    follow[previous_token].insert(first_of_next.begin(), first_of_next.end());
                    follow[previous_token].erase(epsilon);
                }
            }
        }
//    if A  aB is a production rule or A  aBb is a production rule and e is in First(b):
//      everything in FOLLOW(A) is FOLLOW(B)
        while (true)
        {
            bool changed = false;
            for (std::pair<std::string, std::vector<std::vector<std::string>>> production : productions)
            {
                std::string lhs_non_terminal = production.first;
                for(const std::vector<std::string>& rule: production.second)
                {
                    int n = (int)rule.size()-1;
                    std::string s;
                    do
                    {
                        s = rule[n--];
                        int original_size = (int) follow[s].size();
                        follow[s].insert(follow[lhs_non_terminal].begin(), follow[lhs_non_terminal].end());
                        changed |= (original_size != (int) follow[s].size());
                    } while (n>=0 && first[s].count(epsilon));
                }
            }
            if (!changed) break;
        }
}
std::string ParsingTableBuilder::get_last_non_terminal(int &index, std::vector<std::string> vector)
{
    std::string res;
    if(index < 0)
    {
        return res;
    }
    std::string current = vector[index];
    if(is_terminal[current])
    {
        return res;
    }
    else if(index == vector.size()-1 || first[vector[index+1]].count(epsilon)>0)
    {
        res = current;
    }
    index --;
    return res;
}


