#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

struct Point {
    float x, y;
};

class Entity {
public:
    virtual ~Entity() = default;
    virtual void translate(float dx, float dy) = 0;
    virtual void rotate(float cx, float cy, float angle) = 0;
    virtual void scale(float cx, float cy, float factor) = 0;

    virtual std::string toSvg() = 0;
    virtual void toPgm(std::vector<std::vector<int>>& pixels) = 0;
};


#endif
