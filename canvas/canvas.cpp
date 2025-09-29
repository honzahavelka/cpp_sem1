#include "canvas.h"


Canvas::Canvas(int width, int height) : width{ width }, height{ height } {
}

void Canvas::translate(float dx, float dy) {
    for (auto &e : entities) {
        e->translate(dx, dy);
    }
}

void Canvas::rotate(float cx, float cy, float angle) {
    for (auto &e : entities) {
        e->rotate(cx, cy, angle);
    }
}

void Canvas::scale(float cx, float cy, float factor) {
    for (auto &e : entities) {
        e->scale(cx, cy, factor);
    }
}

void Canvas::addEntity(std::unique_ptr<Entity> entity) {
    entities.push_back(std::move(entity));
}



