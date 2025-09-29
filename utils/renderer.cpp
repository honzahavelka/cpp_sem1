#include "renderer.h"
#include "../canvas/canvas.h"

#include <iostream>
#include <fstream>
#include <sstream>


void Renderer::SVGRender(const Canvas &canvas, std::string &filename) {
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
        return;
    }
    outFile << oss.str();
}

void Renderer::PGMRender(const Canvas &canvas, std::string &filename) {
}
