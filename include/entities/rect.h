#ifndef SEM_1_V2_RECT_H
#define SEM_1_V2_RECT_H

#include "entities/entity.h"
#include <array>

/**
 * @brief Třída reprezentující obdélník.
 *
 * Obdélník je definován svým levým horním rohem a rozměry.
 *
 * @note Interně je obdélník reprezentován jako pole 4 vrcholů (polygon).
 * Kdybychom si pamatovali jen (x, y, šířka, výška), nedokázali bychom
 * reprezentovat obdélník otočený např. o 45 stupňů.
 */
class Rect final : public Entity {
public:
    /**
     * @brief Vytvoří obdélník ze zadání, levý horní roh + rozměry.
     *
     * Konstruktor okamžitě vypočítá souřadnice všech 4 rohů obdélníku
     * a uloží je do interního pole `m_points`.
     *
     * @param top_left Souřadnice levého horního rohu.
     * @param width Šířka obdélníku.
     * @param height Výška obdélníku.
     */
    Rect(const Point& top_left, const double width, const double height);

    /**
     * @brief Posune obdélník o daný vektor.
     * Aplikuje posun na všechny 4 vrcholy.
     * @param offset Vektor posunu.
     */
    void translate(const Point& offset) override;

    /**
     * @brief Otočí obdélník kolem zadaného středu.
     *
     * Rotace se provádí nad každým ze 4 vrcholů zvlášť. Díky tomu se
     * obdélník správně natočí v prostoru jako celek.
     *
     * @param center Střed rotace.
     * @param angle_deg Úhel ve stupních.
     */
    void rotate(const Point& center, const double angle_deg) override;

    /**
     * @brief Přeškáluje obdélník vůči středu.
     * Změní vzdálenost všech 4 bodů od středu škálování.
     * @param center Střed škálování.
     * @param factor Faktor zvětšení/zmenšení.
     */
    void scale(const Point& center, const double factor) override;

    /**
     * @brief Vykreslí obdélník.
     * Předá sebe sama rendereru, který ho vykreslí.
     * @param renderer Použitý renderer.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Getter pro vrcholy obdélníku.
     * Vrací pole 4 bodů v pořadí: TopLeft, TopRight, BottomRight, BottomLeft.
     * @return Konstantní reference na pole bodů.
     */
    [[nodiscard]] const std::array<Point, 4>& getPoints() const { return m_points; }
private:
    /**
     * @brief Uložení 4 rohů obdélníku.
     * Používáme std::array pro pevný počet bodů bez dynamické alokace.
     * Pořadí bodů je důležité pro vykreslování čar aby se spojily dokola.
     */
    std::array<Point, 4> m_points{};
};

#endif