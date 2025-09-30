#ifndef RECT_H
#define RECT_H
#include <vector>

#include "entity.h"

class Rect : public Entity {
public:
    Rect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

    void translate(float dx, float dy) override;
    void rotate(float cx, float cy, float angle) override;
    void scale(float cx, float cy, float factor) override;

    std::string toSvg() override;
    void toPgm(std::vector<std::vector<int>>& pixels) override;

private:
    std::vector<Point> points;
};



#endif //RECT_H
