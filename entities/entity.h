#ifndef ENTITY_H
#define ENTITY_H

struct Point {
    float x, y;
};

class Entity {
public:
    virtual ~Entity() = default;
    virtual void translate(float dx, float dy);
    virtual void rotate(float cx, float cy, float angle);
    virtual void scale(float cx, float cy, float factor);
};


#endif
