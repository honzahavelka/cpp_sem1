#ifndef COMMAND_H
#define COMMAND_H

#include "../canvas/canvas.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Canvas& canvas) = 0;
};

#endif
