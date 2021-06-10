#include "../def/InputMatcher.h"

//
// Created by Hamza  on 6/9/2021.
//
bool debug_mode = true;
const string epsilon = "\\L";



bool InputMatcher::match_helper(string input, string &log) {
    string cur_token = input;
    string cur_state = stk.back();
    if (debug_mode) {
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
            log = "Couldn't find a match for the input!!";
        } else {
            log = "accept the string :)";
        }
        return true;
    }

    /// A ---- b
    bool terminal = true;
    if (non_terminals.count(cur_state)) {
        terminal = false;
    }
    if (!terminal) {
        // A -> e
        if (table.count(make_pair(cur_state, cur_token))) {
            vector<string> &new_states = table[make_pair(cur_state, cur_token)];
            // push the states backward in the stack
            vector<string> next_production;
            for (auto itr = new_states.rbegin(); itr != new_states.rend(); itr++) {
                if (*itr != epsilon) {
                    stk.push_back(*itr);
                }
                next_production.push_back(*itr);
            }
            reverse(next_production.begin(), next_production.end());
            log += (cur_state + " --> ");
            for (auto l : next_production)
                log += (" " + l);

            return false;
        } else {
            // A -> ec
            // we have to skip input up to the next sync input
            if (!recover[cur_state].count(cur_token)) {
                // this means that we are going to skip the current input until we found a sync or a transition
                log = "Couldn't find a transition, we are going to skip the input " + input;
                stk.push_back(cur_state);
                return true;
            } else {
                log = input + "is in the recovering, we are going to pop " + cur_state;
                // if the above transition doesn't hold, we then ignore the top value of the stack
                return false;
            }
        }

    } else {
        if (cur_state == cur_token) {
            log = "matching the token " + input;
        } else {
            log = "missing " + input + " the token.  " + input + " inserted";
        }
        return true;
    }
    return true;
}

vector<string> InputMatcher::match_one_token(string input) {
    string log = "";
    vector<string> ans;
    bool ok = match_helper(input, log);
    while (!ok) {
        ans.push_back(log);
        std::cout << "Log: " <<  log << std::endl;
        log.clear() ;
        ok = match_helper(input, log);
    }
    std::cout << log << std::endl;
    ans.push_back(log);
    return ans;
}

void InputMatcher::fill_non_terminals() {
    for (auto p : table) {
        non_terminals.insert(p.first.first);
    }
}

vector<string> InputMatcher::match(string input) {
    return match_one_token(input);
}