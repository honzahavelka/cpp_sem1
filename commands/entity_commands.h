#ifndef ENTITY_COMMANDS_H
#define ENTITY_COMMANDS_H

#include "command.h"
class LineCommand : public Command {
public:
    LineCommand(float x1, float y1, float x2, float y2);
    void execute(Canvas& canvas) override;

private:
    float x1, x2, y1, y2;
};

class RectCommand : public Command {
public:
    RectCommand(float x1, float y1, float w, float h);
    void execute(Canvas& canvas) override;

private:
    float x1, x2, x3, x4;
    float y1, y2, y3, y4;
};

class CircleCommand : public Command {
public:
    CircleCommand(float x, float y, float radius);
    void execute(Canvas& canvas) override;

private:
    float x, y;
    float radius;
};

#endif
