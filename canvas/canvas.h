#ifndef CANVAS_H
#define CANVAS_H


#include "../entities/line.h"
#include "../entities/rect.h"
#include "../entities/circle.h"

class Canvas {

public:
    Canvas(int width, int height);
    ~Canvas() = default;

    void translate(float dx, float dy);
    void rotate(float cx, float cy, float angle);
    void scale(float cx, float cy, float factor);

    void addEntity(std::unique_ptr<Entity> entity);

    int getWidth() const;
    int getHeight() const;

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

private:
    int width, height;
    std::vector<std::unique_ptr<Entity>> entities;
};



#endif //CANVAS_H
