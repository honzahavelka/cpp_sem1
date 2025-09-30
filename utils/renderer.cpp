#include "renderer.h"
#include "../canvas/canvas.h"

#include <iostream>
#include <fstream>
#include <sstream>


bool Renderer::SVGRender(const Canvas &canvas, std::string &filename) {
    std::ostringstream oss;

    oss << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << canvas.getWidth() << "\" "
        << "height=\"" << canvas.getHeight() << "\" "
        << "style=\"background-color:#FFFFFF\">" << std::endl;

    for (const auto& e : canvas.getEntities()) {
        oss << e->toSvg() << "\n";
    }

    oss << "</svg>\n";

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Error: cannot open output file " << filename << "." << std::endl;
        return false;
    }
    outFile << oss.str();
    return true;
}

bool Renderer::PGMRender(const Canvas &canvas, std::string &filename) {
    std::ostringstream oss;

    std::vector<std::vector<int>> pixels(
        canvas.getHeight(),
        std::vector<int>(canvas.getWidth(), 1)
    );

    for (const auto& e : canvas.getEntities()) {
        e->toPgm(pixels);
    }

    oss << "P2\n";
    oss << canvas.getWidth() << " " << canvas.getHeight() << "\n";
    oss << "1" << "\n";

    for (int y = 0; y < pixels.size(); y++) {
        for (int x = 0; x < pixels[0].size(); x++) {
            oss << pixels[y][x] << " ";
        }
        oss << "\n";
    }

    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error: can't open file " << filename << "\n";
        return false;
    }
    out << oss.str();
    return true;
}
