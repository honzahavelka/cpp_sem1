#ifndef SEM_1_V2_CIRCLE_H
#define SEM_1_V2_CIRCLE_H

#include "entities/entity.h"

class Circle final : public Entity {
public:
    Circle(const Point& center, const double radius);

    void translate(const Point& offset) override;
    void rotate(const Point& center, const double angle_deg) override;
    void scale(const Point& scale, const double factor) override;

    void draw(Renderer& renderer) const override;

    const Point& getCenter() const { return m_center; }
    const double getRadius() const { return m_radius; }

private:
    Point m_center;
    double m_radius;
};

#endif