#include "renderers/pgm_renderer.h"

#include "entities/line.h"
#include "entities/circle.h"
#include "entities/rect.h"
#include <fstream>
#include <cmath>

PgmRenderer::PgmRenderer(const std::string& filename, const int width, const int height)
    : m_filename(filename), m_width(width), m_height(height)
{
    // inicializace pixelového bufferu.
    // PGM formát používá 8bitovou šedou škálu (0-255).
    // plátno inicializujeme bílou barvou (255), protože kreslíme černou (0).
    // vektor používáme jako 1D pole reprezentující 2D mřížku.
    m_pixels.resize(width * height, 255);
}

void PgmRenderer::putPixel(const int x, const int y, const uint8_t color) {
    // kontrolujeme, jestli se souřadnice vejdou do vektoru, jestli ne, tak nezapisujeme
    // color je defaultně nastaven na 0, protože se v projektu jinak nevyužívá
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_pixels[y * m_width + x] = color;
    }
}


void PgmRenderer::drawThickLine(int x0, int y0, const int x1, const int y1) {
    // rozhodnutí o strmosti čáry.
    // pokud je rozdíl v Y větší než v X, čára je strmá -> je lepší ji dělat tlustou na ose X
    // a naopak
    const bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    // příprava proměnných pro Bresenhamův algoritmus
    const int dx = std::abs(x1 - x0);
    const int dy = std::abs(y1 - y0);
    const int sx = (x0 < x1) ? 1 : -1;  // směr kroku v ose X
    const int sy = (y0 < y1) ? 1 : -1;  // směr kroku v ose Y
    int err = dx - dy;                  // chyba nasčítavájící se v průběhu kreslení

    while (true) {
        // vykreslení hlavního pixelu čáry
        putPixel(x0, y0, 0);

        // aby čára byla tlustá 2 px, přidáme pixel v kolmém směru na hlavní osu kreslení.
        if (steep) {
            // čára je svislá -> ztloustneme ji do šířky
            putPixel(x0 + 1, y0, 0);
        } else {
            // čára je vodorovná -> ztloustneme ji do výšky
            putPixel(x0, y0 + 1, 0);
        }

        // konec cyklu, pokud jsme dosáhli koncového bodu
        if (x0 == x1 && y0 == y1) break;

        // výpočet dalšího kroku Bresenhama
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
    // lambda funkce pro zaokrouhlení souřadnic, vím že to asi není úplně dobré využití
    // nějak sem ale zadání splnit musel a jinde jsem si taky nebyl jistý
    auto toInt = [](const double val) {
        return static_cast<int>(std::round(val));
    };

    // převedení na int a zavolání pomocné metody
    const int x1 = toInt(line.getP1().x);
    const int y1 = toInt(line.getP1().y);
    const int x2 = toInt(line.getP2().x);
    const int y2 = toInt(line.getP2().y);

    drawThickLine(x1, y1, x2, y2);
}

void PgmRenderer::drawBresenhamCircle(const int xm, const int ym, const int r) {
    // Bresenhamův Midpoint algoritmus pro kružnici.
    int x = 0;
    int y = r;
    int d = 3 - 2 * r; // rozhodovací parametr

    while (y >= x) {
        // využití symetrie kruhu.
        // stačí spočítat 1/8 kruhu a zbytek získáme zrcadlením
        putPixel(xm + x, ym + y, 0);
        putPixel(xm - x, ym + y, 0);
        putPixel(xm + x, ym - y, 0);
        putPixel(xm - x, ym - y, 0);
        putPixel(xm + y, ym + x, 0);
        putPixel(xm - y, ym + x, 0);
        putPixel(xm + y, ym - x, 0);
        putPixel(xm - y, ym - x, 0);

        x++;
        // aktualizace rozhodovací proměnné
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
    // pokusíme se udělat tloušťku 2 px
    if (r >= 1) {
        drawBresenhamCircle(xm, ym, r - 1);
    }
}

void PgmRenderer::drawRect(const Rect& rect) {
    const auto& pts = rect.getPoints();

    // obdélník vykreslíme jako 4 spojené úsečky.
    // Procházíme vrcholy: 0->1, 1->2, 2->3, 3->0
    for (size_t i = 0; i < 4; ++i) {
        const int x1 = static_cast<int>(std::round(pts[i].x));
        const int y1 = static_cast<int>(std::round(pts[i].y));

        // index druhého bodu spočítaný modulem, aby se spojila 3 -> 0
        const int x2 = static_cast<int>(std::round(pts[(i + 1) % 4].x));
        const int y2 = static_cast<int>(std::round(pts[(i + 1) % 4].y));

        drawThickLine(x1, y1, x2, y2);
    }
}

void PgmRenderer::save() {
    // check souboru
    std::ofstream ofs(m_filename);
    if (!ofs.is_open()) {
        throw std::runtime_error("Nelze zapsat PGM: " + m_filename);
    }

    // zápis hlavičky PGM formátu, verze P2 = ASCII text
    // struktura:
    // P2
    // sirka vyska
    // max_hodnota_sede - zde 255
    ofs << "P2\n";
    ofs << m_width << " " << m_height << "\n";
    ofs << "255\n";

    // zápis dat
    for (size_t i = 0; i < m_pixels.size(); ++i) {
        // static cast protože jinak by stream napsal z uint8_t ASCII char
        ofs << static_cast<int>(m_pixels[i]) << " ";

        // odřázkování po šířce není nutnost, ale je to hezčí
        if ((i + 1) % m_width == 0) ofs << "\n";
    }
}