#include "renderers/pgm_renderer.h"

#include "entities/line.h"
#include "entities/circle.h"
#include "entities/rect.h"
#include <fstream>
#include <cmath>

PgmRenderer::PgmRenderer(const std::string& filename, const int width, const int height)
    : m_filename(filename), m_width(width), m_height(height)
{
    // Inicializace bílou barvou (255)
    m_pixels.resize(width * height, 255);
}

void PgmRenderer::putPixel(const int x, const int y, const uint8_t color) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_pixels[y * m_width + x] = color;
    }
}

void PgmRenderer::drawThickLine(int x0, int y0, const int x1, const int y1) {

    const bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    const int dx = std::abs(x1 - x0);
    const int dy = std::abs(y1 - y0);
    const int sx = (x0 < x1) ? 1 : -1;
    const int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // Kreslíme hlavní pixel (černá = 0)
        putPixel(x0, y0, 0);

        // --- TADY JE TA MAGIE PRO TLOUŠŤKU 2PX ---
        if (steep) {
            // Čára je svislá -> ztloustneme ji do šířky (x+1)
            putPixel(x0 + 1, y0, 0);
        } else {
            // Čára je vodorovná -> ztloustneme ji do výšky (y+1)
            putPixel(x0, y0 + 1, 0);
        }
        // ------------------------------------------

        if (x0 == x1 && y0 == y1) break;
        const int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void PgmRenderer::drawLine(const Line& line) {
    // Zadání: tloušťka 2 pixely.
    // Jednoduchý trik: nakreslíme čáru a pak ji posuneme o 1px vedle.
    // Pro věrnost by to chtělo složitější logiku, ale pro semestrálku stačí
    // zdvojit čáru v jedné ose.

    auto toInt = [](const double val) {
        return static_cast<int>(std::round(val));
    };

    const int x1 = toInt(line.getP1().x);
    const int y1 = toInt(line.getP1().y);
    const int x2 = toInt(line.getP2().x);
    const int y2 = toInt(line.getP2().y);

    drawThickLine(x1, y1, x2, y2);
}

void PgmRenderer::drawBresenhamCircle(const int xm, const int ym, const int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        // Vykreslení 8 symetrických bodů (oktantů)
        putPixel(xm + x, ym + y, 0);
        putPixel(xm - x, ym + y, 0);
        putPixel(xm + x, ym - y, 0);
        putPixel(xm - x, ym - y, 0);
        putPixel(xm + y, ym + x, 0);
        putPixel(xm - y, ym + x, 0);
        putPixel(xm + y, ym - x, 0);
        putPixel(xm - y, ym - x, 0);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void PgmRenderer::drawCircle(const Circle& circle) {
    const int xm = static_cast<int>(std::round(circle.getCenter().x));
    const int ym = static_cast<int>(std::round(circle.getCenter().y));
    const int r = static_cast<int>(std::round(circle.getRadius()));

    drawBresenhamCircle(xm, ym, r);
    if (r >= 1) {
        drawBresenhamCircle(xm, ym, r - 1);
    }
}

void PgmRenderer::drawRect(const Rect& rect) {
    // Obdélník je jen 4 úsečky
    const auto& pts = rect.getPoints();

    // Kreslíme hrany: 0-1, 1-2, 2-3, 3-0
    for (size_t i = 0; i < 4; ++i) {
        const int x1 = static_cast<int>(std::round(pts[i].x));
        const int y1 = static_cast<int>(std::round(pts[i].y));

        // Následující bod (modulo zajistí spojení 3->0)
        const int x2 = static_cast<int>(std::round(pts[(i + 1) % 4].x));
        const int y2 = static_cast<int>(std::round(pts[(i + 1) % 4].y));

        drawThickLine(x1, y1, x2, y2);
    }
}

void PgmRenderer::save() {
    std::ofstream ofs(m_filename, std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Nelze zapsat PGM: " + m_filename);
    }

    // PGM hlavička (P5 = binární, P2 = ASCII)
    // Zadání odkazuje na specifikaci, P2 je bezpečnější pro ladění, P5 je menší.
    // Použijeme P2 (ASCII), protože je čitelnější a stačí.
    ofs << "P2\n";
    ofs << m_width << " " << m_height << "\n";
    ofs << "255\n"; // Max hodnota šedé

    for (size_t i = 0; i < m_pixels.size(); ++i) {
        ofs << static_cast<int>(m_pixels[i]) << " ";
        // Pro hezčí formátování odřádkujeme po šířce
        if ((i + 1) % m_width == 0) ofs << "\n";
    }
}