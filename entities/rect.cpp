#include "rect.h"
#include "line.h"

#include <sstream>

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

        float newX = xShift * cosA - yShift * sinA + cx;
        float newY = xShift * sinA + yShift * cosA + cy;

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

std::string Rect::toSvg() {
    std::vector<Line> edges;

    edges.emplace_back(points[0].x, points[0].y, points[1].x, points[1].y);
    edges.emplace_back(points[1].x, points[1].y, points[3].x, points[3].y);
    edges.emplace_back(points[3].x, points[3].y, points[2].x, points[2].y);
    edges.emplace_back(points[2].x, points[2].y, points[0].x, points[0].y);


    std::ostringstream oss;
    for (auto& line : edges) {
        oss << line.toSvg() << "\n";
    }
    return oss.str();
}

void Rect::toPgm(std::vector<std::vector<int>>& pixels) {
    std::vector<Line> edges;

    edges.emplace_back(points[0].x, points[0].y, points[1].x, points[1].y);
    edges.emplace_back(points[1].x, points[1].y, points[3].x, points[3].y);
    edges.emplace_back(points[3].x, points[3].y, points[2].x, points[2].y);
    edges.emplace_back(points[2].x, points[2].y, points[0].x, points[0].y);

    for (auto& line : edges) {
        line.toPgm(pixels);
    }
}
