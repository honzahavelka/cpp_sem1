#include "rect.h"


Rect::Rect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    points.reserve(4);
    points.emplace_back(x1, y1);
    points.emplace_back(x2, y2);
    points.emplace_back(x3, y3);
    points.emplace_back(x4, y4);
}

void Rect::translate(float dx, float dy) {
    for (auto& p : points) {
        p.x += dx;
        p.y += dy;
    }
}

void Rect::rotate(float cx, float cy, float angle) {
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

    for (auto& p : points) {
        rotatePoint(p.x, p.y);
    }
}

void Rect::scale(float cx, float cy, float factor) {
    /* lambda func */
    auto scalePoint = [&](float& x, float& y) {
        x = (x - cx) * factor + cx;
        y = (y - cy) * factor + cy;
    };

    for (auto& p : points) {
        scalePoint(p.x, p.y);
    }
}
