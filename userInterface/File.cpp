//
// Created by Manfi on 06/06/21.
//

#include "File.h"
#include <regex>
#include <fstream>

File::File(std::string path) {
    this->path = path;
}

File::~File() {}

int categorize(std::string &line) {
    std::string space = "(\\s)*";
    std::string startLine = space + "#" + space;
    std::string id = "[a-zA-Z][a-zA-Z0-9_]*" + space;
    std::string eq = "=" + space;
    std::string terminal = R"(((\'.+\')|(\\L)))" + space;
    std::string subVal = "((" + id + "|" + terminal + ")(\\s+" + id + "|" + terminal + ")*)" + space;
    std::string val = "(" + subVal + "(\\|" + space + subVal + ")*)";
    std::string originalExpression = startLine + id + eq + val;
    std::string continueExpression = space + "(\\|" + space + subVal + ")+";
    std::regex regOriginal(originalExpression);
    std::regex regContinue(continueExpression);
    if (regex_match(line,regOriginal)) return File::ORIGINAL;
    if (regex_match(line,regContinue)) return File::CONTINUE;
    return 0;
}

std::vector<std::vector<std::string>> divideProduction(std::string &expression, int st) {
    std::vector<std::vector<std::string>> val;
    while(st < expression.size()) {
        std::vector<std::string> tmp;
        while(st < expression.size() and expression[st] not_eq '|') {
            if (expression[st] == ' ') {
                st++; continue;
            }
            std::string str = "";
            while(st < expression.size() and expression[st] not_eq '|' and expression[st] not_eq ' ') {
                if (expression[st] != '\'') str += expression[st];
                st++;
            }
            tmp.push_back(str);
        }
        if (tmp.size()) val.push_back(tmp);
        ++st;
    }
    return val;
}

void File::addExpression(std::string expression) {
    if (expression.empty()) return;
    std::string key = "";
    int i = 0;
    for(; expression[i] not_eq '='; ++i) {
        if (expression[i] == ' ' or expression[i] == '#') continue;
        key+=expression[i];
    }
    expressions[key] = divideProduction(expression, i+1);
}

void File::readFromFile(std::ifstream &file){
    std::string line, exp = "";
    while(std::getline(file, line)) {
        if (line.empty()) continue;
        int category = categorize(line);
        if (not category or exp.empty() and category == File::CONTINUE) throw line;
        if (category == File::CONTINUE) exp += line;
        else {
            addExpression(exp);
            exp = line;
        }
    }
    addExpression(exp);
}

void sendToParserTable() {
    //call method of salama to send map
}

void File::go() {
    std::ifstream file(path);
    readFromFile(file);
    file.close();
    sendToParserTable();
}
