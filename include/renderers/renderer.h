#ifndef SEM_1_V2_RENDERER_H
#define SEM_1_V2_RENDERER_H

class Line;
class Rect;
class Circle;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void drawLine(const Line& line) = 0;
    virtual void drawCircle(const Circle& circle) = 0;
    virtual void drawRect(const Rect& rect) = 0;

    virtual void save() = 0;
};

#endif