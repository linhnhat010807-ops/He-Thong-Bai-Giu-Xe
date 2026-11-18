
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Menu.h"

int main(int argc, char* argv[]) {
    std::stringstream cleanInput;

    // Chi doc file khi nguoi dung truyen ten file vao tham so.
    if (argc > 1) {
        const std::string testFile = argv[1];
        std::ifstream inFile(testFile);

        if (inFile.is_open()) {
            std::string line;

            while (std::getline(inFile, line)) {
                if (line.empty()) continue;
                cleanInput << line << "\n";
            }

            std::cin.rdbuf(cleanInput.rdbuf());
        } else {
            std::cerr << "Khong mo duoc file " << testFile
                      << ". Chuyen sang nhap tu ban phim.\n";
        }
    }

    runProgram();

    return 0;
}
