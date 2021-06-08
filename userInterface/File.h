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
    void addExpression(std::string expression);
    void readFromFile(std::ifstream &file);
public:
    static const char ORIGINAL = 'o';
    static const char CONTINUE = 'c';
    File(std::string path);
    ~File();
    void go();
};


#endif //PHASE2_FILE_H
