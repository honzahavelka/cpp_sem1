#ifndef SEM_1_V2_ENTITY_H
#define SEM_1_V2_ENTITY_H

#include "utils/point.h"

class Renderer;

class Entity {
public:
    virtual ~Entity() = default;

    virtual void translate(const Point& offset) = 0;
    virtual void rotate(const Point& center, const double angle_deg) = 0;
    virtual void scale(const Point& scale, const double factor) = 0;

    virtual void draw(Renderer& renderer) const = 0;
};

#endif