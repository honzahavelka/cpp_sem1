#ifndef SEM_1_V2_SVG_RENDERER_H
#define SEM_1_V2_SVG_RENDERER_H

#include "renderers/renderer.h"

#include <string>
#include <vector>

class SvgRenderer final : public Renderer {
public:
    SvgRenderer(const std::string& filename, const int width, const int height);

    void drawLine(const Line& line) override;
    void drawCircle(const Circle& circle) override;
    void drawRect(const Rect& rect) override;
    void save() override;

private:
    std::string m_filename;
    int m_width;
    int m_height;
    std::vector<std::string> m_buffer;
};
#endif