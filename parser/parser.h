#ifndef PARSER_H
#define PARSER_H

#include <fstream>

#include "../commands/command.h"

class Parser {
public:
    Parser(const std::string& filename);
    ~Parser() = default;
    bool parseFile();
    std::unique_ptr<Command> parseLine(std::string& line);

    std::vector<std::unique_ptr<Command>>& getCommands();
    int getCommandsCount() const;

private:
    int commandsCount;
    std::ifstream file;
    std::vector<std::unique_ptr<Command>> commands;
};



#endif //PARSER_H
