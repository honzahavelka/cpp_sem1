#include "utils/args_parser.h"
#include <filesystem>
#include <stdexcept>
#include <sstream>

ArgsParser::ArgsParser(int argc, char* argv[]) {
    if (argc != 4) {
        throw std::runtime_error("Nespravny pocet argumentu.\nPouziti: drawing.exe <input.txt> <output.pgm|svg> <width>x<height>");
    }

    validateInputFile(argv[1]);
    validateOutputFile(argv[2]);
    parseCanvasSize(argv[3]);

    m_config.input_file = argv[1];
    m_config.output_file = argv[2];
}

void ArgsParser::validateInputFile(const std::string& path) const {
    if (path.size() < 4 || path.substr(path.size() - 4) != ".txt") {
        throw std::runtime_error("Vstupni soubor '" + path + "' musi mit priponu .txt");
    }

    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Vstupni soubor '" + path + "' neexistuje.");
    }

    checkInvalidChars(path, "Vstupni soubor");
}

void ArgsParser::validateOutputFile(const std::string& path) {
    const bool is_pgm = (path.size() >= 4 && path.substr(path.size() - 4) == ".pgm");
    const bool is_svg = (path.size() >= 4 && path.substr(path.size() - 4) == ".svg");

    if (!is_pgm && !is_svg) {
        throw std::runtime_error("Vystupni soubor '" + path + "' musi mit priponu .pgm nebo .svg");
    }

    if (is_pgm) m_config.format = "pgm";
    else if (is_svg) m_config.format = "svg";

    checkInvalidChars(path, "Vystupni soubor");
}

void ArgsParser::checkInvalidChars(const std::string& path, const std::string& context) const {
    const std::string invalidChars = "/\\:*?\"<>|";
    for (char c : path) {
        if (invalidChars.find(c) != std::string::npos) {
            throw std::runtime_error(context + " obsahuje nepovoleny znak: '" + std::string(1, c) + "'");
        }
    }
}

void ArgsParser::parseCanvasSize(const std::string& size_str) {
    const size_t x_pos = size_str.find('x');
    if (x_pos == std::string::npos) {
        throw std::runtime_error("Neplatny format rozmeru plátna: '" + size_str + "'. Ocekavan format WxH (napr. 800x600).");
    }

    try {
        const std::string w_part = size_str.substr(0, x_pos);
        const std::string h_part = size_str.substr(x_pos + 1);

        if (w_part.empty() || h_part.empty()) throw std::invalid_argument("Chybejici hodnota");

        m_config.width = std::stoi(w_part);
        m_config.height = std::stoi(h_part);

        if (m_config.width <= 0 || m_config.height <= 0) {
            throw std::out_of_range("Rozmery musi byt vetsi nez nula.");
        }
    } catch (const std::exception&) {
        throw std::runtime_error("Rozmery plátna '" + size_str + "' musi byt dve kladna cela cisla oddelena 'x'.");
    }
}