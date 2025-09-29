#ifndef CIRCLE_H
#define CIRCLE_H
#include "entity.h"

class Circle : public Entity {
public:
    Circle(float x, float y, float radius);

    void translate(float dx, float dy) override;
    void rotate(float cx, float cy, float angle) override;
    void scale(float cx, float cy, float factor) override;

    std::string toSvg() override;

private:
    Point center{};
    float radius;
};



#endif //CIRCLE_H
