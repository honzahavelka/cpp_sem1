#ifndef SEM_1_V2_LINE_H
#define SEM_1_V2_LINE_H

#include "entity.h"

class Line final : public Entity {
public:
    Line(const Point& p1, const Point& p2);

    void translate(const Point& offset) override;
    void rotate(const Point& center, const double angle_deg) override;
    void scale(const Point& scale, const double factor) override;

    void draw(Renderer& renderer) const override;

    const Point& getP1() const { return m_p1; }
    const Point& getP2() const { return m_p2; }
private:
    Point m_p1;
    Point m_p2;
};

#endif