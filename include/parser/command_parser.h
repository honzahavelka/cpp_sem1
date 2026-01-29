#ifndef SEM_1_V2_COMMAND_PARSER_H
#define SEM_1_V2_COMMAND_PARSER_H

#include "entities/entity.h"

#include <vector>
#include <string>
#include <memory>

class CommandParser {
public:
    std::vector<std::unique_ptr<Entity>> parse(const std::string& filename);

    const int getNumberOfCommands() const { return m_number_of_commands; }

private:
    int m_current_line = 0;
    int m_number_of_commands = 0;
    std::vector<std::unique_ptr<Entity>> m_entities;

    void processLine(const std::string& line);
    std::string stripComment(const std::string& line) const;

};

#endif