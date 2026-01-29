#ifndef SEM_1_V2_RECT_H
#define SEM_1_V2_RECT_H

#include "entities/entity.h"

class Rect final : public Entity {
public:
    Rect(const Point& top_left, const double width, const double height);

    void translate(const Point& offset) override;
    void rotate(const Point& center, const double angle_deg) override;
    void scale(const Point& scale, const double factor) override;

    void draw(Renderer& renderer) const override;

    const std::array<Point, 4>& getPoints() const { return m_points; }
private:

    std::array<Point, 4> m_points;
};

#endif