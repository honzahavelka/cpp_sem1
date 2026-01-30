#include "entities/circle.h"

#include "renderers/renderer.h"

Circle::Circle(const Point &center, const double radius) : m_center(center), m_radius(radius) {}


void Circle::translate(const Point &offset) {
    // posouvá se pouze střed, poloměr se nemění
    m_center = m_center + offset;
}

void Circle::rotate(const Point &center, const double angle_deg) {
    const double rad = angle_deg * (M_PI / 180.0);

    // zase se posouvá pouze střed
    m_center = m_center.rotateAround(center, rad);
}

void Circle::scale(const Point &center, const double factor) {
    // scalujeme střed, vzorec popsán v line.cpp
    m_center = (m_center - center) * factor + center;
    // rádius se změní podle faktoru
    m_radius *= factor;
}

void Circle::draw(Renderer& renderer) const {
    renderer.drawCircle(*this);
}
