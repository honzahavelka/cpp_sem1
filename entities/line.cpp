#include <cmath>

#include "line.h"
#include <sstream>

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

        float newX = xShift * cosA - yShift * sinA + cx;
        float newY = xShift * sinA + yShift * cosA + cy;

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

std::string Line::toSvg() {
    std::ostringstream oss;
    oss << "<line "
        << "x1=\"" << p1.x << "\" "
        << "y1=\"" << p1.y << "\" "
        << "x2=\"" << p2.x << "\" "
        << "y2=\"" << p2.y << "\" "
        << "stroke=\"black\" stroke-width=\"2\" />";
    return oss.str();
}

void Line::toPgm(std::vector<std::vector<int>>& pixels) {

    /* easier version of Bresenham's algorithm, that uses floats */
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float step = std::max(std::abs(dx), std::abs(dy));
    if (step != 0) {
        float stepX = dx / step;
        float stepY = dy / step;

        for (int i = 0; i <= step; i++) {
            int xPx = std::round(p1.x + i * stepX);
            int yPx = std::round(p1.y + i * stepY);

            if (xPx >= 0 && xPx < pixels.size() && yPx >= 0 && yPx < pixels[0].size()) {
                pixels[yPx][xPx] = 0;
            }
        }
    }
}
