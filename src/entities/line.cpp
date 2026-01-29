#include "entities/line.h"

#include "renderers/renderer.h"

#include <cmath>

Line::Line(const Point& p1, const Point& p2) : m_p1(p1), m_p2(p2) {}


void Line::translate(const Point& offset) {
    m_p1 = m_p1 + offset;
    m_p2 = m_p2 + offset;
}

void Line::rotate(const Point& center, const double angle_deg) {
    const double rad = angle_deg * (M_PI / 180.0);

    m_p1 = m_p1.rotateAround(center, rad);
    m_p2 = m_p2.rotateAround(center, rad);
}

void Line::scale(const Point& scale, const double factor) {
    m_p1 = (m_p1 - scale) * factor + scale;
    m_p2 = (m_p2 - scale) * factor + scale;
}

void Line::draw(Renderer& renderer) const {
    renderer.drawLine(*this);
}


