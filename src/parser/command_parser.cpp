#include "parser/command_parser.h"

#include <fstream>
#include <ostream>
#include <sstream>

#include "entities/circle.h"
#include "entities/line.h"
#include "entities/rect.h"

std::vector<std::unique_ptr<Entity>> CommandParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nelze otevrit vstupni soubor: " + filename);
    }

    m_entities.clear();
    m_current_line = 0;

    std::string line;
    while (std::getline(file, line)) {
        m_current_line++;

        const std::string clean_line = stripComment(line);
        if (clean_line.empty() || clean_line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        try {
            processLine(clean_line);
            m_number_of_commands++;
        } catch (const std::exception& e) {
            throw std::runtime_error("Chyba na radku " + std::to_string(m_current_line) + ": " + e.what());
        }
    }

    return std::move(m_entities);
}

void CommandParser::processLine(const std::string& line) {
    std::stringstream ss(line);
    std::string command;

    ss >> command;

    if (command == "line") {
        int x1, y1, x2, y2;
        if (!(ss >> x1 >> y1 >> x2 >> y2)) throw std::runtime_error("Line: Ocekavano x1 y1 x2 y2");

        if (x1 == x2 && y1 == y2) throw std::runtime_error("Line: Krajni body nesmi splyvat");

        m_entities.push_back(std::make_unique<Line>(Point{static_cast<double>(x1), static_cast<double>(y1)},
                                                      Point{static_cast<double>(x2), static_cast<double>(y2)}));
    }
    else if (command == "circle") {
        int x, y;
        double r;
        if (!(ss >> x >> y >> r)) throw std::runtime_error("Circle: Ocekavano x y r");

        if (r <= 0) throw std::runtime_error("Circle: Polomer musi byt > 0");

        m_entities.push_back(std::make_unique<Circle>(Point{static_cast<double>(x), static_cast<double>(y)}, r));
    }
    else if (command == "rect") {
        int x, y;
        double w, h;

        if (!(ss >> x >> y >> w >> h)) throw std::runtime_error("Rect: Ocekavano x y w h");

        if (w <= 0 || h <= 0) throw std::runtime_error("Rect: Sirka a vyska musi byt > 0");

        m_entities.push_back(std::make_unique<Rect>(Point{static_cast<double>(x), static_cast<double>(y)}, w, h));
    }
    else if (command == "translate") {
        int dx, dy;
        if (!(ss >> dx >> dy)) throw std::runtime_error("Translate: Ocekavano dx dy");

        for (const auto& e : m_entities) {
            e->translate(Point{static_cast<double>(dx), static_cast<double>(dy)});
        }
    }
    else if (command == "rotate") {
        int x, y;
        double angle;

        if (!(ss >> x >> y >> angle)) throw std::runtime_error("Rotate: Ocekavano x y angle");
        for (const auto& e : m_entities) {
            e->rotate(Point{static_cast<double>(x), static_cast<double>(y)}, angle);
        }
    }
    else if (command == "scale") {
        int x, y;
        double scale;

        if (!(ss >> x >> y >> scale)) throw std::runtime_error("Scale: Ocekavano x y scale");
        if (scale == 0) throw std::runtime_error("Scale: Faktor nesmi byt 0");

        for (const auto& e : m_entities) {
            e->scale(Point{static_cast<double>(x), static_cast<double>(y)}, scale);
        }
    }
    else {
        throw std::runtime_error("Neznama instrukce: " + command);
    }
}

std::string CommandParser::stripComment(const std::string& line) const {
    const size_t commentPos = line.find('#');
    if (commentPos != std::string::npos) {
        return line.substr(0, commentPos);
    }
    return line;
}