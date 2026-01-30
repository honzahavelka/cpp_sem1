#include "entities/rect.h"

#include "renderers/renderer.h"

Rect::Rect(const Point &top_left, const double width, const double height) {
    // důležité je pořadí, aby se body spojily dokola
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
    // posunut všech bodů
    for (auto& p : m_points) {
        p = p + offset;
    }
}

void Rect::rotate(const Point &center, const double angle_deg) {
    // funkce rotateAround pracuje s RADIANY
    const double rad = angle_deg * (M_PI / 180.0);
    for (auto& p : m_points) {
        p = p.rotateAround(center, rad);
    }
}

void Rect::scale(const Point &center, const double factor) {
    // scalujeme všechny body
    // vzorec popsán v line.cpp
    for (auto& p : m_points) {
        p = (p - center) * factor + center;
    }
}

void Rect::draw(Renderer& renderer) const {
    // předání sama sebe rendereru
    renderer.drawRect(*this);
}
