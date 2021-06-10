//
// Created by Manfi on 06/06/21.
//

#include "File.h"
#include <regex>
#include <fstream>
#include <set>
#include "../def/ParsingTableBuilder.h"
#include "../def/InputMatcher.h"

File::File(std::string path) {
    this->path = path;
}

File::~File() {}

int categorize(std::string &line) {
    static std::string space = "(\\s)*";
    static std::string startLine = space + "#" + space;
    static std::string id = "[a-zA-Z][a-zA-Z0-9_]*" + space;
    static std::string eq = "=" + space;
    static std::string terminal = R"(((\'.+\')|(\\L)))" + space;
    static std::string subVal = "((" + id + "|" + terminal + ")(\\s+" + id + "|" + terminal + ")*)" + space;
    static std::string val = "(" + subVal + "(\\|" + space + subVal + ")*)";
    static std::string originalExpression = startLine + id + eq + val;
    static std::string continueExpression = space + "(\\|" + space + subVal + ")+";
    static std::regex regOriginal(originalExpression);
    static std::regex regContinue(continueExpression);
    if (regex_match(line, regOriginal)) return File::ORIGINAL;
    if (regex_match(line, regContinue)) return File::CONTINUE;
    return 0;
}

std::vector<std::vector<std::string>> File::divideProduction(std::string &expression, int st) {
    std::vector<std::vector<std::string>> val;
    while (st < expression.size()) {
        std::vector<std::string> tmp;
        while (st < expression.size() and expression[st] not_eq '|') {
            if (expression[st] == ' ') {
                st++;
                continue;
            }
            std::string str = "";
            if (expression[st] == '\'') {
                ++st;
                while (expression[st] not_eq '\'') {
                    str += expression[st++];
                }
                ++st;
                is_terminal[str] = true;
            } else {
                while (st < expression.size() and expression[st] not_eq '|' and expression[st] not_eq ' ') {
                    str += expression[st++];
                }
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
    for (; expression[i] not_eq '='; ++i) {
        if (expression[i] == ' ' or expression[i] == '#') continue;
        key += expression[i];
    }
    static bool ok = (start = key, true);

    expressions[key] = divideProduction(expression, i + 1);
}

void File::readFromFile(std::ifstream &file) {
    std::string line, exp = "";
    while (std::getline(file, line)) {
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

void File::sendToParserTable() {
    ParsingTableBuilder parsingTableBuilder(expressions, is_terminal, start);
    parsingTableBuilder.build();
    InputMatcher::getInstance().setTable(parsingTableBuilder.get_table(), parsingTableBuilder.get_sync_table(), "METHOD_BODY") ;
//    // int id , id , id ;
    vector<string> input = {"int", "id", ";", "$"};
    for (auto token : input) {
        InputMatcher::getInstance().match(token);
    }
    std::cerr << "Input matching finished " << std::endl;
}

void File::go() {
    std::ifstream file(path);
    readFromFile(file);
    file.close();
    sendToParserTable();
}
