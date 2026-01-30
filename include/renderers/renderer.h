#ifndef SEM_1_V2_RENDERER_H
#define SEM_1_V2_RENDERER_H

class Line;
class Rect;
class Circle;

/**
 * @brief Abstraktní rozhraní pro vykreslování grafických objektů.
 *
 * Třída definuje sadu metod, které musí každá konkrétní implementace rendereru
 * (např. SvgRenderer, PgmRenderer) splnit. Eentity volají tyto metody a předávají
 * samy sebe k vykreslení.
 */
class Renderer {
public:
    /**
     * @brief Virtuální destruktor.
     * Zajišťuje správné uvolnění paměti při mazání odvozených tříd
     * přes ukazatel na bázovou třídu Renderer.
     */
    virtual ~Renderer() = default;

    /**
     * @brief Vykreslí úsečku.
     * @param line Reference na objekt úsečky s jejími souřadnicemi.
     */
    virtual void drawLine(const Line& line) = 0;

    /**
     * @brief Vykreslí kružnici.
     * @param circle Reference na objekt kružnice se středem a poloměrem.
     */
    virtual void drawCircle(const Circle& circle) = 0;

    /**
     * @brief Vykreslí obdélník.
     * @param rect Reference na objekt obdélníku (reprezentován 4 vrcholy).
     */
    virtual void drawRect(const Rect& rect) = 0;

    /**
     * @brief Dokončí a uloží výsledek do souboru.
     *
     * Tato metoda slouží k finalizaci výstupu – např. zapsání SVG patičky.
     */
    virtual void save() = 0;
};

#endif