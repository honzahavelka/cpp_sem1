#ifndef SEM_1_V2_PMG_RENDERER_H
#define SEM_1_V2_PMG_RENDERER_H

#include "renderer.h"

#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Implementace rendereru pro formát PGM.
 *
 * Tato třída provádí tzv. rasterizaci – převádí vektorové tvary
 * na mřížku pixelů. Využívá k tomu algoritmy pro vykreslování
 * úseček a kružnic - Bresenhamův algoritmus.
 * Výsledkem je černobílý obrázek uložený v textovém P2 formátu.
 */
class PgmRenderer final : public Renderer {
public:
    /**
     * @brief Inicializuje renderer a alokuje paměť pro pixely.
     *
     * @param filename Cesta k výstupnímu souboru.
     * @param width Šířka plátna v pixelech.
     * @param height Výška plátna v pixelech.
     */
    PgmRenderer(const std::string& filename, const int width, const int height);

    /**
     * @brief Rasterizuje úsečku do pixelového bufferu.
     * Volá interní metodu drawThickLine.
     * @param line Úsečka k vykreslení.
     */
    void drawLine(const Line& line) override;

    /**
     * @brief Rasterizuje kružnici.
     * Volá interní metodu drawBresenhamCircle.
     * @param circle Kružnice k vykreslení.
     */
    void drawCircle(const Circle& circle) override;

    /**
     * @brief Rasterizuje obdélník.
     * Vykreslí obdélník jako 4 spojené úsečky (polygon).
     * @param rect Obdélník k vykreslení.
     */
    void drawRect(const Rect& rect) override;

    /**
     * @brief Zapíše obsah pixelového bufferu do souboru.
     * Vygeneruje hlavičku PGM formátu P2 a následně vypíše hodnoty všech pixelů.
     */
    void save() override;

private:
    std::string m_filename;
    int m_width;                ///< Šířka plátna.
    int m_height;               ///< Výška plátna.

    /**
     * @brief Paměť pro uložení pixelů.
     *
     * Jedná se o jednorozměrné pole reprezentující 2D mřížku.
     * Mapování souřadnic je: index = y * width + x.
     * Hodnota 0 = černá, 255 = bílá.
     */
    std::vector<uint8_t> m_pixels;

    /**
     * @brief Bezpečně zapíše pixel do bufferu.
     *
     * Metoda kontroluje, zda jsou souřadnice [x, y] uvnitř hranic plátna.
     * Pokud jsou mimo, zápis ignoruje (clipping), aby nedošlo k pádu programu.
     *
     * @param x Souřadnice X.
     * @param y Souřadnice Y.
     * @param color Hodnota barvy (defaultně 0 = černá).
     */
    void putPixel(const int x, const int y, const uint8_t color = 0);

    /**
     * @brief Vykreslí úsečku s tloušťkou 2px pomocí Bresenhamova algoritmu.
     *
     * Metoda v závislosti na sklonu čáry
     * zdvojuje pixely buď v ose X nebo Y, aby byla tloušťka opticky konzistentní.
     *
     * @param x0 X souřadnice začátku.
     * @param y0 Y souřadnice začátku.
     * @param x1 X souřadnice konce.
     * @param y1 Y souřadnice konce.
     */
    void drawThickLine(int x0, int y0, const int x1, const int y1);

    /**
     * @brief Vykreslí kružnici pomocí Bresenhamova algoritmu pro kružnice.
     *
     * Používá celočíselnou aritmetiku pro rychlý výpočet bodů na obvodu.
     * Využívá 8-cestnou symetrii kruhu.
     *
     * @param xm X souřadnice středu.
     * @param ym Y souřadnice středu.
     * @param r Poloměr.
     */
    void drawBresenhamCircle(const int xm, const int ym, const int r);
};

#endif