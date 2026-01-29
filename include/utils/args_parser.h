#ifndef SEM_1_V2_ARGS_PARSER_H
#define SEM_1_V2_ARGS_PARSER_H

#include <string>
#include <vector>

class ArgsParser {
public:
    // Struktura pro přehledné uložení výsledků
    struct Config {
        std::string input_file;
        std::string output_file;
        int width;
        int height;
        std::string format; // "pgm" nebo "svg"
    };

    // Konstruktor, který rovnou provede validaci
    ArgsParser(int argc, char* argv[]);

    // Getter pro získání výsledné konfigurace
    const Config& getConfig() const { return m_config; }

private:
    Config m_config;

    void validateInputFile(const std::string& path) const;
    void validateOutputFile(const std::string& path);
    void parseCanvasSize(const std::string& size_str);
    void checkInvalidChars(const std::string& path, const std::string& context) const;
};

#endif