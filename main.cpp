#include <iostream>
#include "userInterface/File.h"

int main() {
    File file("../input.txt");
    try{
        file.go();
    } catch (std::string line) {
        std::cout << "Error in input file please review it and try again." << std::endl;
        std::cout << "In line " + line << std::endl;
    }

    return 0;
}
