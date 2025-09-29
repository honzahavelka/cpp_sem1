#ifndef TRANSFORM_COMMANDS_H
#define TRANSFORM_COMMANDS_H

#include "command.h"

class TranslateCommand : public Command {
public:
    TranslateCommand(float dx, float dy);
    void execute(Canvas& canvas) override;
private:
    float dx, dy;
};

class RotateCommand : public Command {
public:
    RotateCommand(float cx, float cy, float angle);
    void execute(Canvas& canvas) override;
private:
    float cx, cy, angle;
};

class ScaleCommand : public Command {
public:
    ScaleCommand(float cx, float cy, float factor);
    void execute(Canvas& canvas) override;

private:
    float cx, cy, factor;
};

#endif
