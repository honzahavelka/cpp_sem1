#include "circle.h"

#include <cmath>

Circle::Circle(float x, float y, float radius) : radius { radius } {
    center = Point{x, y};
}

void Circle::translate(float dx, float dy) {
    center.x += dx;
    center.y += dy;
}

void Circle::rotate(float cx, float cy, float angle) {
    float rad = angle * static_cast<float>(M_PI) / 180.0f;
    float cosA = std::cosf(rad);
    float sinA = std::sinf(rad);

    float xShift = center.x - cx;
    float yShift = center.y - cy;
    center.x = xShift * cosA - yShift * sinA;
    center.y = xShift * sinA + yShift * cosA;
}

void Circle::scale(float cx, float cy, float factor) {
    center.x = (center.x - cx) * factor + cx;
    center.y = (center.y - cy) * factor + cy;

    radius *= factor;
}
