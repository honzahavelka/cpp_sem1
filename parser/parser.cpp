#include "parser.h"
#include "../commands/entity_commands.h"
#include "../commands/transform_commands.h"

#include <iostream>
#include <sstream>


Parser::Parser(const std::string &filename) {
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Error: can't open input file " << filename << "." << std::endl;
        exit(2);
    }
    commandsCount = 0;
}

int Parser::getCommandsCount() const {
    return commandsCount;
}


std::vector<std::unique_ptr<Command>>& Parser::getCommands() {
    return commands;
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

        auto cmd = parseLine(line);
        if (cmd) {
            commandsCount++;
            commands.push_back(std::move(cmd));
        }
        else {
            std::cout << "On line number " << lineNumber << "." << std::endl;
            return false;
        }
    }
    return true;
}

std::unique_ptr<Command> Parser::parseLine(std::string& line) {
    std::istringstream inputss(line);

    std::string keyword;
    inputss >> keyword;

    if (keyword == "line") {
        int x1, y1, x2, y2;
        if (!(inputss >> x1 >> y1 >> x2 >> y2))
            return nullptr;

        if (x1 == x2 && y1 == y2) {
            std::cout << "Error: can't parse line " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<LineCommand>(x1, y1, x2, y2);
    }
    if (keyword == "rect") {
        int x1, y1;
        float w, h;
        if (!(inputss >> x1 >> y1 >> w >> h))
            return nullptr;

        if (w <= 0 || h <= 0) {
            std::cout << "Error: can't parse line " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<RectCommand>(x1, y1, w, h);
    }
    if (keyword == "circle") {
        int x, y;
        float r;
        if (!(inputss >> x >> y >> r))
            return nullptr;

        if (r <= 0) {
            std::cout << "Error: can't parse line " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<CircleCommand>(x, y, r);
    }
    if (keyword == "translate") {
        int dx, dy;
        if (!(inputss >> dx >> dy))
            return nullptr;
        return std::make_unique<TranslateCommand>(dx, dy);
    }
    if (keyword == "scale") {
        int cx, cy;
        float factor;
        if (!(inputss >> cx >> cy >> factor))
            return nullptr;

        if (factor == 0) {
            std::cout << "Error: can't parse line " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<ScaleCommand>(cx, cy, factor);
    }
    if (keyword == "rotate") {
        int cx, cy;
        float angle;
        if (!(inputss >> cx >> cy >> angle))
            return nullptr;
        return std::make_unique<RotateCommand>(cx, cy, angle);
    }

    std::cout << "Error: can't parse line " << line << std::endl;
    return nullptr;
}
