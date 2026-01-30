#include "entities/line.h"
#include "renderers/renderer.h"

#include <cmath>

Line::Line(const Point& p1, const Point& p2) : m_p1(p1), m_p2(p2) {}


void Line::translate(const Point& offset) {
    // využijtí přetíženého operátoru struktury point
    // jednoduchý posun bodů
    m_p1 = m_p1 + offset;
    m_p2 = m_p2 + offset;
}


void Line::rotate(const Point& center, const double angle_deg) {
    // převod, protože funkce rotateAround chce radiány
    const double rad = angle_deg * (M_PI / 180.0);

    // využití funkce struktury Point
    m_p1 = m_p1.rotateAround(center, rad);
    m_p2 = m_p2.rotateAround(center, rad);
}


void Line::scale(const Point& center, const double factor) {
    // vzorec pro škálování bodu P vůči středu C: P' = C + (P - C) * factor

    // 1. (m_p1 - center) -> vektor od středu škálování k bodu
    // 2. * factor -> změna délky vektoru
    // 3. + center -> posun zpět
    m_p1 = (m_p1 - center) * factor + center;
    m_p2 = (m_p2 - center) * factor + center;
}

void Line::draw(Renderer& renderer) const {
    // objekt neví jak sám sebe nakreslit, tak to hodí na renderer
    renderer.drawLine(*this);
}


