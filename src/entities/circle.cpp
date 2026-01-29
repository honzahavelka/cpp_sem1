#include "entities/circle.h"

#include "renderers/renderer.h"

Circle::Circle(const Point &center, const double radius) : m_center(center), m_radius(radius) {}

void Circle::translate(const Point &offset) {
    m_center = m_center + offset;
}

void Circle::rotate(const Point &center, const double angle_deg) {
    const double rad = angle_deg * (M_PI / 180.0);

    m_center = m_center.rotateAround(center, rad);
}

void Circle::scale(const Point &scale, const double factor) {
    m_center = (m_center - scale) * factor + scale;
    m_radius *= factor;
}

void Circle::draw(Renderer& renderer) const {
    renderer.drawCircle(*this);
}
