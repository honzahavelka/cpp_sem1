#ifndef SEM_1_V2_LINE_H
#define SEM_1_V2_LINE_H

#include "entity.h"

/**
 * @brief Třída reprezentující úsečku ve 2D prostoru.
 *
 * Úsečka je definována dvěma krajními body (začátek a konec).
 * Implementuje všechny geometrické transformace vyžadované rozhraním Entity.
 */
class Line final : public Entity {
public:
    /**
     * @brief Vytvoří novou úsečku zadanou dvěma body.
     * @param p1 Počáteční bod úsečky.
     * @param p2 Koncový bod úsečky.
     */
    Line(const Point& p1, const Point& p2);

    /**
     * @brief Posune úsečku o daný vektor.
     * Přičte vektor posunu k oběma koncovým bodům (p1 i p2).
     * @param offset Vektor posunu (dx, dy).
     */
    void translate(const Point& offset) override;

    /**
     * @brief Otočí úsečku kolem zadaného středu.
     * Provede rotaci obou koncových bodů kolem středu.
     * @param center Střed rotace.
     * @param angle_deg Úhel ve stupních.
     */
    void rotate(const Point& center, const double angle_deg) override;

    /**
     * @brief Přeškáluje úsečku (změní její délku a pozici vůči středu).
     * @param center Střed škálování.
     * @param factor Faktor zvětšení/zmenšení.
     */
    void scale(const Point& center, const double factor) override;

    /**
     * @brief Vykreslí úsečku.
     * Předá instanci sebe sama (`*this`) metodě `renderer.drawLine()`.
     * @param renderer Použitý renderer.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Getter pro počáteční bod.
     * @return Konstantní reference na první bod.
     */
    [[nodiscard]] const Point& getP1() const { return m_p1; }

    /**
     * @brief Getter pro koncový bod.
     * @return Konstantní reference na druhý bod.
     */
    [[nodiscard]] const Point& getP2() const { return m_p2; }

private:
    Point m_p1;
    Point m_p2;
};

#endif