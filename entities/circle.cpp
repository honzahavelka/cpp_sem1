#include "circle.h"

#include <cmath>
#include <sstream>

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
    center.x = xShift * cosA - yShift * sinA + cx;
    center.y = xShift * sinA + yShift * cosA + cy;
}

void Circle::scale(float cx, float cy, float factor) {
    center.x = (center.x - cx) * factor + cx;
    center.y = (center.y - cy) * factor + cy;

    radius *= factor;
}

std::string Circle::toSvg() {
    std::ostringstream oss;
    oss << "<circle "
        << "cx=\"" << center.x << "\" "
        << "cy=\"" << center.y << "\" "
        << "r=\"" << radius << "\" "
        << "stroke=\"black\" stroke-width=\"2\" "
        << "fill=\"none\" />";
    return oss.str();
}

void Circle::toPgm(std::vector<std::vector<int>>& pixels) {

    /* top of circle */
    float x = 0;
    float y = -radius;

    auto draw = [&](float py, float px) {
        int xr = std::round(px);
        int yr = std::round(py);
        if (yr >= 0 && yr < pixels.size() &&
            xr >= 0 && xr < pixels[0].size()) {
            pixels[yr][xr] = 0;
        }
    };

    /* iterate through 1/8 of the circle to the right */
    while (x < -y) {
        float yMid = y + 0.5f;
        if (x*x + yMid*yMid > radius*radius) {
            y+=1;
        }
        draw(center.y + y, center.x + x);
        draw(center.y + y, center.x - x);
        draw(center.y - y, center.x + x);
        draw(center.y - y, center.x - x);
        draw(center.y + x, center.x + y);
        draw(center.y + x, center.x - y);
        draw(center.y - x, center.x + y);
        draw(center.y - x, center.x - y);

        x += 1;
    }
}