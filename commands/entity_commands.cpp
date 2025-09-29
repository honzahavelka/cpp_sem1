#include "entity_commands.h"


LineCommand::LineCommand(float x1, float y1, float x2, float y2) : x1 { x1 }, x2 { x2 }, y1{ y1 }, y2 { y2 } {
}

void LineCommand::execute(Canvas& canvas) {
    canvas.addEntity(std::make_unique<Line>(x1, y1, x2, y2));
}

RectCommand::RectCommand(float x1, float y1, float w, float h) : x1 { x1 }, y1 { y1 } {
    x2 = x4 = x1 + w;
    x3 = x1;
    y2 = y1;
    y3 = y4 = y1 + h;
}

void RectCommand::execute(Canvas& canvas) {
    canvas.addEntity(std::make_unique<Rect>(x1, y1, x2, y2, x3, y3, x4, y4));
}

CircleCommand::CircleCommand(float x, float y, float radius) : x { x }, y { y }, radius { radius } {
}

void CircleCommand::execute(Canvas& canvas) {
    canvas.addEntity(std::make_unique<Circle>(x, y, radius));
}



