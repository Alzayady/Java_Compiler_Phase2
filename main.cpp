#include <iostream>
#include "userInterface/File.h"
#include <unordered_map>
#include "FirstAndFollowTester.h"

int main() {
    FirstAndFollowTester firstAndFollowTester;
    firstAndFollowTester.unit_test();
    File file("../input.txt");
    try{
        file.go();
    } catch (std::string line) {
        std::cout << "Error in input file please review it and try again." << std::endl;
        std::cout << "In line " + line << std::endl;
    }
    std::cout << "DONE!" << std::endl;
    return 0;
}
