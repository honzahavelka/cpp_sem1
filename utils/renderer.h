#ifndef RENDERER_H
#define RENDERER_H

#include "../canvas/canvas.h"

class Renderer {
public:
    static bool SVGRender(const Canvas& canvas, std::string& filename);
    static bool PGMRender(const Canvas& canvas, std::string& filename);
};

#endif
