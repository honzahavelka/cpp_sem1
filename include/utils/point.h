#ifndef SEM_1_V2_POINT_H
#define SEM_1_V2_POINT_H
#include <valarray>

struct Point {
    double x;
    double y;

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }

    Point operator*(const double factor) const {
        return {x * factor, y * factor};
    }

    Point rotateAround(const Point& center, const double angle) const {
        const double s = std::sin(angle);
        const double c = std::cos(angle);

        const Point shift = *this - center;

        const double new_x = c * shift.x - s * shift.y;
        const double new_y = s * shift.x + c * shift.y;

        return {new_x + center.x, new_y + center.y};
    }
};

#endif