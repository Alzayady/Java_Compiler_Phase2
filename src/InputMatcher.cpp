//

#include "../def/InputMatcher.h"

//
// Created by Hamza  on 6/9/2021.
//
bool debug_mode = false;
const string epsilon = "Epsilon";

vector<string> InputMatcher::match_helper(vector<string> input) {
    unordered_set<string> non_terminals;
    for (auto p : table) {
        non_terminals.insert(p.first.first);
    }
    vector<string> stk;
    stk.push_back("$");
    stk.push_back(start);
    vector<string> ans;

    int size = (int) input.size();
    bool found_match = false;
    for (int i = 0; i < size;) {

        string cur_token = input[i];
        string cur_state = stk.back();
        if (debug_mode) {
            std::cout << "Iteration number: " << i << std::endl;
            std::cout << "Stack: ";
            for (auto &t : stk)
                std::cout << t << ' ';
            std::cout << std::endl;
//        std::cout << cur_state << ' ' << cur_token << ' ' << ans.back() << std::endl;

            std::cout << "Current_state: " << cur_state << std::endl;
            std::cout << "Current token: " << cur_token << std::endl;
        }

        stk.pop_back();
        if (cur_state == "$") {
            if (cur_token != "$") {
                ans.emplace_back("Couldn't find a match for the input");
            } else {
                ans.emplace_back("accept the string");
            }
            return ans;
        }


        bool terminal = true;
        if (non_terminals.count(cur_state)) {
            terminal = false;
        }
        if (!terminal) {
            if (table.count(make_pair(cur_state, cur_token))) {
                vector<string> &new_states = table[make_pair(cur_state, cur_token)];
                // push the states backward in the stack
                vector<string> logs;
                for (auto itr = new_states.rbegin(); itr != new_states.rend(); itr++) {
                    if (*itr != epsilon) {
                        stk.push_back(*itr);
                    }
                    logs.push_back(*itr);
                }
                reverse(logs.begin(), logs.end());
                ans.push_back(cur_state + " --> ");
                for (auto log : logs)
                    ans.back() += (" " + log);
            } else {
//                assert(false);
                // we have to skip input up to the next sync input
                if (!recover[cur_state].count(cur_token)) {
                    // this means that we are going to skip the current input until we found a sync or a transition
                    ans.push_back("Couldn't find a transition, we are going to skip the input ");
                    stk.push_back(cur_state);
                    i += 1;
                }
                // if the above transition doesn't hold, we then ignore the top value of the stack
            }

        } else {
            if (cur_state == cur_token) {
                ans.emplace_back("matching the token " + input[i]);
                i++;
            } else {
                ans.emplace_back("missing " + input[i] + " the token " + input[i] + " inserted");
            }
        }
        if (debug_mode)
            std::cout << "Log: " << ans.back() << std::endl;


    }
    if (!stk.empty()) {
        ans.push_back("Couldn't find a match !!!!!!");
    }
    return ans;
}

vector<string> InputMatcher::match(vector<string> input) {
    return match_helper(input);
}
