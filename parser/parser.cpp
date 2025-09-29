#include "parser.h"

#include <iostream>


Parser::Parser(const std::string &filename) {
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Error: can't open input file " << filename << "." << std::endl;
        exit(2);
    }
    lineCount = 0;
}

bool Parser::parseFile() {
    int lineNumber = 0;
    std::string line;

    while (std::getline(file, line)) {
        bool onlyWhiteSpace = true;
        lineNumber++;

        /* check for empty lines */
        for (unsigned char c : line) {
            if (!std::isspace(c)) {
                onlyWhiteSpace = false;
                break;
            }
        }
        if (onlyWhiteSpace) {
            continue;
        }

        /* find and cut out comment */
        auto commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        /*auto cmd = parseLine(line);
        if (cmd) {
            //push into commands
        }
        else {
            //error, invalid line
            return false;
        }*/
    }

    return true;
}
