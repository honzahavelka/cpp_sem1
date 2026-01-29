#ifndef SEM_1_V2_PMG_RENDERER_H
#define SEM_1_V2_PMG_RENDERER_H

#include "renderer.h"

#include <string>
#include <vector>

class PgmRenderer final : public Renderer {
public:
    PgmRenderer(const std::string& filename, const int width, const int height);

    void drawLine(const Line& line) override;
    void drawCircle(const Circle& circle) override;
    void drawRect(const Rect& rect) override;
    void save() override;

private:
    std::string m_filename;
    int m_width;
    int m_height;

    std::vector<uint8_t> m_pixels;

    void putPixel(const int x, const int y, const uint8_t color = 0);

    void drawThickLine(int x0, int y0, const int x1, const int y1);
    void drawBresenhamCircle(const int xm, const int ym, const int r);
};
#endif