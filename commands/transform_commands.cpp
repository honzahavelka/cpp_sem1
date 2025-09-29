#include "transform_commands.h"


TranslateCommand::TranslateCommand(float dx, float dy) : dx { dx }, dy { dy } {
}

void TranslateCommand::execute(Canvas& canvas) {
    canvas.translate(dx, dy);
}

RotateCommand::RotateCommand(float cx, float cy, float angle) : cx { cx }, cy { cy }, angle { angle } {
}

void RotateCommand::execute(Canvas& canvas) {
    canvas.rotate(cx, cy, angle);
}

ScaleCommand::ScaleCommand(float cx, float cy, float factor) : cx { cx }, cy { cy }, factor { factor } {
}


void ScaleCommand::execute(Canvas &canvas) {
    canvas.scale(cx, cy, factor);
}


