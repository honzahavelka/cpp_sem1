#include <cmath>

#include "line.h"

Line::Line(float x1, float y1, float x2, float y2) {
    p1 = Point{x1, y1};
    p2 = Point{x2, y2};
}

void Line::translate(float dx, float dy) {
    p1.x += dx;
    p1.y += dy;
    p2.x += dx;
    p2.y += dy;
}

void Line::rotate(float cx, float cy, float angle) {
    float rad = angle * static_cast<float>(M_PI) / 180.0f;
    float cosA = std::cosf(rad);
    float sinA = std::sinf(rad);

    /* lambda func */
    auto rotatePoint = [&](float& x, float& y) {
        float xShift = x - cx;
        float yShift = y - cy;

        float newX = xShift * cosA - yShift * sinA;
        float newY = xShift * sinA + yShift * cosA;

        x = newX;
        y = newY;
    };

    rotatePoint(p1.x, p1.y);
    rotatePoint(p2.x, p2.y);
}

void Line::scale(float cx, float cy, float factor) {
    /* lambda func */
    auto scalePoint = [&](float& x, float& y) {
        x = (x - cx) * factor + cx;
        y = (y - cy) * factor + cy;
    };

    scalePoint(p1.x, p1.y);
    scalePoint(p2.x, p2.y);
}

