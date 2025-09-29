#ifndef LINE_H
#define LINE_H
#include "entity.h"

class Line : public Entity {
public:
    Line(float x1, float y1, float x2, float y2);

    void translate(float dx, float dy) override;
    void rotate(float cx, float cy, float angle) override;
    void scale(float cx, float cy, float factor) override;

private:
    Point p1, p2;
};



#endif //LINE_H
