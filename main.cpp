#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Menu.h"

int main() {
    
    std::stringstream cleanInput;
    std::ifstream inFile("parking_testcases.cases");
    if (inFile.is_open()) {
        std::string line;

        while (std::getline(inFile, line)) {

            if (line.empty()) continue;
            
            cleanInput << line << "\n";
        }
        
        std::cin.rdbuf(cleanInput.rdbuf());
    } else {
        std::cout << "Khong tim thay file parking_testcases.cases!\n";
    }

    runProgram();

    return 0;
}
