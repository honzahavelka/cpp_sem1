#include "entities/rect.h"

#include "renderers/renderer.h"

Rect::Rect(const Point &top_left, const double width, const double height) {
    // top left
    m_points[0] = top_left;
    // top right
    m_points[1] = top_left + Point{width, 0};
    // bottom right
    m_points[2] = top_left + Point{width, height};
    // bottom left
    m_points[3] = top_left + Point{0, height};
}

void Rect::translate(const Point &offset) {
    for (auto& p : m_points) {
        p = p + offset;
    }
}

void Rect::rotate(const Point &center, const double angle_deg) {
    const double rad = angle_deg * (M_PI / 180.0);
    for (auto& p : m_points) {
        p = p.rotateAround(center, rad);
    }
}

void Rect::scale(const Point &scale, const double factor) {
    for (auto& p : m_points) {
        p = (p - scale) * factor + scale;
    }
}

void Rect::draw(Renderer& renderer) const {
    renderer.drawRect(*this);
}
