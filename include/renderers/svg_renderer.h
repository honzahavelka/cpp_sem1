#ifndef SEM_1_V2_SVG_RENDERER_H
#define SEM_1_V2_SVG_RENDERER_H

#include "renderers/renderer.h"

#include <string>
#include <vector>

/**
 * @brief Implementace rendereru pro formát SVG.
 *
 * Tento renderer generuje textový XML soubor popisující geometrické tvary.
 *
 * Implementace funguje tak, že jednotlivé metody `drawX` pouze přidávají
 * XML řetězce do interního bufferu a samotný zápis do souboru proběhne až v metodě `save()`.
 */
class SvgRenderer final : public Renderer {
public:
    /**
     * @brief Inicializuje renderer.
     * @param filename Cesta k výstupnímu souboru.
     * @param width Šířka plátna.
     * @param height Výška plátna.
     */
    SvgRenderer(const std::string& filename, const int width, const int height);

    /**
     * @brief Převede úsečku na SVG značku <line>.
     * Vypočítá souřadnice a přidá do bufferu řetězec:
     * <line x1="..." y1="..." x2="..." y2="..." stroke="black" stroke-width="2" />
     * @param line Úsečka k vykreslení.
     */
    void drawLine(const Line& line) override;

    /**
     * @brief Převede kružnici na SVG značku <circle>.
     * Přidá do bufferu řetězec:
     * <circle cx="..." cy="..." r="..." stroke="black" stroke-width="2" fill="none" />
     * @param circle Kružnice k vykreslení.
     */
    void drawCircle(const Circle& circle) override;

    /**
     * @brief Převede obdélník na SVG značku <polygon>.
     *
     * Protože obdélník může být otočený, nepoužíváme značku <rect>,
     * ale raději univerzální <polygon>, kterému předáme souřadnice všech 4 rohů.
     *
     * @param rect Obdélník k vykreslení.
     */
    void drawRect(const Rect& rect) override;

    /**
     * @brief Vygeneruje výsledný soubor.
     *
     * 1. Otevře soubor pro zápis.
     * 2. Zapíše standardní XML/SVG hlavičku s rozměry plátna.
     * 3. Vypíše obsah bufferu (všechny tagy).
     * 4. Zapíše ukončovací značku </svg>.
     */
    void save() override;

private:
    std::string m_filename;
    int m_width;
    int m_height;

    /**
     * @brief Vyrovnávací paměť pro SVG příkazy.
     * Místo abychom zapisovali do souboru při každém zavolání drawX, ukládáme si vygenerované
     * XML řádky do tohoto vektoru. Do souboru se zapíšou hromadně v metodě save().
     */
    std::vector<std::string> m_buffer;
};
#endif