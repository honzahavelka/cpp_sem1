#ifndef PARSER_H
#define PARSER_H

#include <fstream>

class Parser {
public:
    Parser(const std::string& filename);
    ~Parser() = default;
    bool parseFile();

private:
    int lineCount;
    std::ifstream file;
};



#endif //PARSER_H
