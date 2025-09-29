#ifndef RENDERER_H
#define RENDERER_H

#include "../canvas/canvas.h"

class Renderer {
public:
    static void SVGRender(const Canvas& canvas, std::string& filename);
    static void PGMRender(const Canvas& canvas, std::string& filename);
};

#endif
