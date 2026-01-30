#include "renderers/svg_renderer.h"

#include "entities/line.h"
#include "entities/circle.h"
#include "entities/rect.h"

#include <fstream>

SvgRenderer::SvgRenderer(const std::string& filename, const int width, const int height)
: m_filename(filename), m_width(width), m_height(height) {}

void SvgRenderer::drawLine(const Line &line) {
    const std::string tag = "<line x1=\"" + std::to_string(line.getP1().x) +
                      "\" y1=\"" + std::to_string(line.getP1().y) +
                      "\" x2=\"" + std::to_string(line.getP2().x) +
                      "\" y2=\"" + std::to_string(line.getP2().y) +
                      "\" stroke=\"black\" stroke-width=\"2\" />";
    m_buffer.push_back(tag);
}

void SvgRenderer::drawCircle(const Circle& circle) {
    const std::string tag = "<circle cx=\"" + std::to_string(circle.getCenter().x) +
                      "\" cy=\"" + std::to_string(circle.getCenter().y) +
                      "\" r=\"" + std::to_string(circle.getRadius()) +
                      "\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />";
    m_buffer.push_back(tag);
}

void SvgRenderer::drawRect(const Rect& rect) {
    std::string pointsAttr;
    for (const auto& p : rect.getPoints()) {
        pointsAttr += std::to_string(p.x) + "," + std::to_string(p.y) + " ";
    }
    // místo rect používáme polygon, alternativa by byla kreslit 4x Line
    const std::string tag = "<polygon points=\"" + pointsAttr +
                      "\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />";
    m_buffer.push_back(tag);
}


void SvgRenderer::save() {
    // check souboru
    std::ofstream ofs(m_filename);
    if (!ofs.is_open()) {
        throw std::runtime_error("Nelze otevrit soubor pro zapis: " + m_filename);
    }

    // hlavička
    ofs << "<svg version=\"1.1\" width=\"" << m_width << "\" height=\"" << m_height
        << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    // pozadí
    ofs << "<rect width=\"100%\" height=\"100%\" fill=\"white\" />\n";

    // vyprázdnit buffer
    for (const auto& tag : m_buffer) {
        ofs << "  " << tag << "\n";
    }

    // konec
    ofs << "</svg>";
    ofs.close();
}