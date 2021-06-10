//
// Created by Salama on 6/8/2021.
//

#ifndef JAVA_COMPILER_PHASE2_FIRSTANDFOLLOWTESTER_H
#define JAVA_COMPILER_PHASE2_FIRSTANDFOLLOWTESTER_H
bool zayady_debug_mode = false;

#include <set>
#include "./def/ParsingTableBuilder.h"
#include "def/InputMatcher.h"

class FirstAndFollowTester {
public:
    static void unit_test() {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions = generate_productions();
        std::unordered_map<std::string, bool> is_terminal = generate_is_terminal_map();

        ParsingTableBuilder parsingTableBuilder(productions, is_terminal, "E");
        parsingTableBuilder.build();
        std::unordered_map<std::string, std::set<std::pair<std::vector<std::string>, std::string>>> first = parsingTableBuilder.get_first();
        std::unordered_map<std::string, std::unordered_set<std::string>> follow = parsingTableBuilder.get_follow();
        parsingTableBuilder.run_extract_table();
        auto it = parsingTableBuilder.get_table();
        auto itt = parsingTableBuilder.get_sync_table();
        if (zayady_debug_mode) {
            for (auto a : it) {
                std::cout << a.first.first << "  " << a.first.second << std::endl;
                for (auto b : a.second) {
                    std::cout << b << " ";
                }

                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "=================================" << std::endl;

            }
            std::cout << "sync" << std::endl;
            for (auto a : itt) {
                std::cout << a.first << "  " << std::endl;
                for (auto b : a.second) {
                    std::cout << b << " ";
                }
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "=================================" << std::endl;
            }

        }


    }

    static std::unordered_map<std::string, bool> generate_is_terminal_map() {
        std::unordered_map<std::string, bool> is_terminal;
        is_terminal.insert({"T'", false});
        is_terminal.insert({"F", false});
        is_terminal.insert({"T", false});
        is_terminal.insert({"E", false});
        is_terminal.insert({"E'", false});
        is_terminal.insert({"id", true});
        is_terminal.insert({"(", true});
        is_terminal.insert({")", true});
        is_terminal.insert({"*", true});
        is_terminal.insert({"+", true});
        return is_terminal;
    }

    static std::unordered_map<std::string, std::vector<std::vector<std::string>>> generate_productions() {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
        std::vector<std::vector<std::string>> vv1;
        std::vector<std::string> v1;
        v1.emplace_back("T");
        v1.emplace_back("E'");
        vv1.push_back(v1);
        std::vector<std::vector<std::string>> vv2;
        std::vector<std::string> v21;
        v21.emplace_back("+");
        v21.emplace_back("T");
        v21.emplace_back("E'");
        std::vector<std::string> v22;
        v22.emplace_back("Epsilon");
        vv2.push_back(v21);
        vv2.push_back(v22);
        std::vector<std::vector<std::string>> vv3;
        std::vector<std::string> v3;
        v3.emplace_back("F");
        v3.emplace_back("T'");
        vv3.push_back(v3);
        std::vector<std::vector<std::string>> vv4;
        std::vector<std::string> v41;
        v41.emplace_back("(");
        v41.emplace_back("E");
        v41.emplace_back(")");
        std::vector<std::string> v42;
        v42.emplace_back("id");
        vv4.push_back(v41);
        vv4.push_back(v42);
        std::vector<std::vector<std::string>> vv5;
        std::vector<std::string> v51;
        v51.emplace_back("*");
        v51.emplace_back("F");
        v51.emplace_back("T'");
        std::vector<std::string> v52;
        v52.emplace_back("Epsilon");
        vv5.push_back(v51);
        vv5.push_back(v52);

        productions.insert({"E", vv1});
        productions.insert({"E'", vv2});
        productions.insert({"T", vv3});
        productions.insert({"F", vv4});
        productions.insert({"T'", vv5});

        if (zayady_debug_mode) {
            for (auto &production: productions) {
                std::cout << production.first + " --> ";
                for (auto &x: production.second) {
                    for (auto &y: x) {
                        std::cout << y + " ";
                    }
                    std::cout << "| ";
                }
                std::cout << std::endl;
            }

        }
        return productions;
    }
};


#endif //JAVA_COMPILER_PHASE2_FIRSTANDFOLLOWTESTER_H
