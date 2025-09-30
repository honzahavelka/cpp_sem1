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
            std::cout << "Line number " << lineNumber << "." << std::endl;
            return false;
        }
    }
    return true;
}

void skipWhiteSpaces(std::string& line, int& i) {
    for (; i < line.size(); i++) {
        if (line[i] == ' ') {
            continue;
        }
        break;
    }
}

std::string loadToken(std::string& line, int& i) {
    std::string token;
    for (; i < line.size(); i++) {
        if (line[i] == ' ') {
            break;
        }
        token += line[i];
    }
    return token;
}

std::unique_ptr<Command> Parser::parseLine(std::string& line) {
    std::string keyword;
    std::vector<std::string> tokens;

    int i;
    for (i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            continue;
        }
        break;
    }
    for (; i < line.size(); i++) {
        if (line[i] == ' ') {
            break;
        }
        keyword += line[i];
    }

    /* LINE */
    if (keyword == "line") {
        while (i < line.size()) {
            skipWhiteSpaces(line, i);
            if (i < line.size()) {
                tokens.push_back(loadToken(line, i));
            }
        }
        if (tokens.size() != 4) {
            std::cout << "Error: wrong number of tokens: " << line << std::endl;
            return nullptr;
        }
        int x1, y1, x2, y2;
        try {
            size_t idx;
            x1 = std::stoi(tokens[0], &idx);
            if (idx != tokens[0].size()) throw std::invalid_argument("extra");
            y1 = std::stoi(tokens[1], &idx);
            if (idx != tokens[1].size()) throw std::invalid_argument("extra");
            x2 = std::stoi(tokens[2], &idx);
            if (idx != tokens[2].size()) throw std::invalid_argument("extra");
            y2 = std::stoi(tokens[3], &idx);
            if (idx != tokens[3].size()) throw std::invalid_argument("extra");

        } catch (const std::invalid_argument& e) {
            std::cout << "Error: wrong data types: " << line << std::endl;
            return nullptr;
        }
        if (x1 == x2 && y1 == y2) {
            std::cout << "Error: entity line cant start and end at the same point: " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<LineCommand>(x1, y1, x2, y2);
    }

    /* RECT */
    if (keyword == "rect") {
        while (i < line.size()) {
            skipWhiteSpaces(line, i);
            if (i < line.size()) {
                tokens.push_back(loadToken(line, i));
            }
        }
        if (tokens.size() != 4) {
            std::cout << "Error: wrong number of tokens: " << line << std::endl;
            return nullptr;
        }
        int x, y, w, h;
        try {
            size_t idx;
            x = std::stoi(tokens[0], &idx);
            if (idx != tokens[0].size()) throw std::invalid_argument("extra");
            y = std::stoi(tokens[1]);
            if (idx != tokens[1].size()) throw std::invalid_argument("extra");
            w = std::stoi(tokens[2]);
            if (idx != tokens[2].size()) throw std::invalid_argument("extra");
            h = std::stoi(tokens[3]);
            if (idx != tokens[3].size()) throw std::invalid_argument("extra");

        } catch (const std::invalid_argument& e) {
            std::cout << "Error: wrong data types: " << line << std::endl;
            return nullptr;
        }
        if (w <= 0 || h <= 0) {
            std::cout << "Error: width and height must be greater than 0. " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<RectCommand>(x, y, w, h);
    }

    /* CIRCLE */
    if (keyword == "circle") {
        while (i < line.size()) {
            skipWhiteSpaces(line, i);
            if (i < line.size()) {
                tokens.push_back(loadToken(line, i));
            }
        }
        if (tokens.size() != 3) {
            std::cout << "Error: wrong number of tokens: " << line << std::endl;
            return nullptr;
        }
        int x, y;
        float r;
        try {
            size_t idx;
            x = std::stoi(tokens[0], &idx);
            if (idx != tokens[0].size()) throw std::invalid_argument("extra");
            y = std::stoi(tokens[1], &idx);
            if (idx != tokens[1].size()) throw std::invalid_argument("extra");
            r = std::stof(tokens[2]);
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: wrong data types: " << line << std::endl;
            return nullptr;
        }
        if (r <= 0) {
            std::cout << "Error: radius must be greater than 0." << line << std::endl;
            return nullptr;
        }
        return std::make_unique<CircleCommand>(x, y, r);
    }

    /* TRANSLATE */
    if (keyword == "translate") {
        while (i < line.size()) {
            skipWhiteSpaces(line, i);
            if (i < line.size()) {
                tokens.push_back(loadToken(line, i));
            }
        }
        if (tokens.size() != 2) {
            std::cout << "Error: wrong number of tokens: " << line << std::endl;
            return nullptr;
        }
        int dx, dy;
        try {
            size_t idx;
            dx = std::stoi(tokens[0], &idx);
            if (idx != tokens[0].size()) throw std::invalid_argument("extra");
            dy = std::stoi(tokens[1]);
            if (idx != tokens[1].size()) throw std::invalid_argument("extra");
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: wrong data types: " << line << std::endl;
            return nullptr;
        }
        return std::make_unique<TranslateCommand>(dx, dy);
    }

    /* SCALE */
    if (keyword == "scale") {
        while (i < line.size()) {
            skipWhiteSpaces(line, i);
            if (i < line.size()) {
                tokens.push_back(loadToken(line, i));
            }
        }
        if (tokens.size() != 3) {
            std::cout << "Error: wrong number of tokens: " << line << std::endl;
            return nullptr;
        }
        int x, y;
        float factor;
        try {
            size_t idx;
            x = std::stoi(tokens[0], &idx);
            if (idx != tokens[0].size()) throw std::invalid_argument("extra");
            y = std::stoi(tokens[1], &idx);
            if (idx != tokens[1].size()) throw std::invalid_argument("extra");
            factor = std::stof(tokens[2]);
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: wrong data types: " << line << std::endl;
            return nullptr;
        }
        if (factor == 0) {
            std::cout << "Error: factor must be greater than 0." << line << std::endl;
            return nullptr;
        }

        return std::make_unique<ScaleCommand>(x, y, factor);
    }

    /* rotate */
    if (keyword == "rotate") {
        while (i < line.size()) {
            skipWhiteSpaces(line, i);
            if (i < line.size()) {
                tokens.push_back(loadToken(line, i));
            }
        }
        if (tokens.size() != 3) {
            std::cout << "Error: wrong number of tokens: " << line << std::endl;
            return nullptr;
        }
        int x, y;
        float angle;

        try {
            size_t idx;
            x = std::stoi(tokens[0], &idx);
            if (idx != tokens[0].size()) throw std::invalid_argument("extra");
            y = std::stoi(tokens[1], &idx);
            if (idx != tokens[1].size()) throw std::invalid_argument("extra");
            angle = std::stof(tokens[2]);
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: wrong data types: " << line << std::endl;
            return nullptr;
        }

        return std::make_unique<RotateCommand>(x, y, angle);
    }

    std::cout << "Error: invalid keyword: " << keyword << ", " << line << std::endl;
    return nullptr;
}