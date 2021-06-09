//
// Created by Manfi on 06/06/21.
//

#ifndef PHASE2_FILE_H
#define PHASE2_FILE_H

#include <iostream>
#include <unordered_map>
#include <vector>

class File {
private:
    std::string path;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> expressions;
    std::string start;
    std::unordered_map<std::string, bool> is_terminal;
    void addExpression(std::string expression);
    void readFromFile(std::ifstream &file);
    void sendToParserTable();
    std::vector<std::vector<std::string>> divideProduction(std::string &expression, int st);
public:
    static const char ORIGINAL = 'o';
    static const char CONTINUE = 'c';
    File(std::string path);
    ~File();
    void go();
};


#endif //PHASE2_FILE_H
