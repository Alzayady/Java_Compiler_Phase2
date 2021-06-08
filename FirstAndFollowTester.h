//
// Created by Salama on 6/8/2021.
//

#ifndef JAVA_COMPILER_PHASE2_FIRSTANDFOLLOWTESTER_H
#define JAVA_COMPILER_PHASE2_FIRSTANDFOLLOWTESTER_H

#include "./def/ParsingTableBuilder.h"

class FirstAndFollowTester {
public:
    static void unit_test(){
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions = generate_productions();
        std::unordered_map<std::string, bool> is_terminal = generate_is_terminal_map();
        ParsingTableBuilder parsingTableBuilder(productions, is_terminal, "E");
        parsingTableBuilder.extract_first();
        parsingTableBuilder.extract_follow();
        std::unordered_map<std::string, std::unordered_set<std::string>> first = parsingTableBuilder.get_first();
        std::unordered_map<std::string, std::unordered_set<std::string>> follow = parsingTableBuilder.get_follow();
        std::cout << "non_terminal\t\tfirst\t\t\tfollow" <<std::endl;
        for(auto &x: first)
        {
            if(!is_terminal[x.first] && x.first!="Epsilon")
            {
                std::string non_terminal = x.first;
                std::cout << x.first + "\t\t\t";
                std::cout << "{ ";
                for(const auto & it : x.second)
                {
                    std::cout << it+", ";
                }
                std::cout << "}\t\t";
                std::cout << "{ ";
                for(const auto & it : follow[x.first])
                {
                    std::cout << it+", ";
                }
                std::cout << "}" << std::endl;
            }
        }
    }
    static std::unordered_map<std::string, bool> generate_is_terminal_map()
    {
        std::unordered_map<std::string, bool> is_terminal;
        is_terminal.insert({"T'",false});
        is_terminal.insert({"F",false});
        is_terminal.insert({"T",false});
        is_terminal.insert({"E",false});
        is_terminal.insert({"E'",false});
        is_terminal.insert({"id",true});
        is_terminal.insert({"(",true});
        is_terminal.insert({")",true});
        is_terminal.insert({"*",true});
        is_terminal.insert({"+",true});
        return is_terminal;
    }
    static std::unordered_map<std::string, std::vector<std::vector<std::string>>> generate_productions()
    {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
        std::vector<std::vector<std::string>> vv1;
        std::vector<std::string> v1;
        v1.emplace_back("T");v1.emplace_back("E'");
        vv1.push_back(v1);
        std::vector<std::vector<std::string>> vv2;
        std::vector<std::string> v21;
        v21.emplace_back("+");v21.emplace_back("T");v21.emplace_back("E'");
        std::vector<std::string> v22;
        v22.emplace_back("Epsilon");
        vv2.push_back(v21);vv2.push_back(v22);
        std::vector<std::vector<std::string>> vv3;
        std::vector<std::string> v3;
        v3.emplace_back("F");v3.emplace_back("T'");
        vv3.push_back(v3);
        std::vector<std::vector<std::string>> vv4;
        std::vector<std::string> v41;
        v41.emplace_back("(");v41.emplace_back("E");v41.emplace_back(")");
        std::vector<std::string> v42;
        v42.emplace_back("id");
        vv4.push_back(v41);vv4.push_back(v42);
        std::vector<std::vector<std::string>> vv5;
        std::vector<std::string> v51;
        v51.emplace_back("*");v51.emplace_back("F");v51.emplace_back("T'");
        std::vector<std::string> v52;
        v52.emplace_back("Epsilon");
        vv5.push_back(v51);vv5.push_back(v52);

        productions.insert({"E", vv1});
        productions.insert({"E'", vv2});
        productions.insert({"T", vv3});
        productions.insert({"F", vv4});
        productions.insert({"T'", vv5});
        for(auto &production: productions)
        {
            std::cout << production.first +" --> ";
            for(auto &x: production.second)
            {
                for(auto &y: x)
                {
                    std::cout << y+" ";
                }
                std::cout << "| " ;
            }
            std::cout << std::endl;
        }
        return productions;
    }
};


#endif //JAVA_COMPILER_PHASE2_FIRSTANDFOLLOWTESTER_H
