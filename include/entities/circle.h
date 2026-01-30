#ifndef SEM_1_V2_CIRCLE_H
#define SEM_1_V2_CIRCLE_H

#include "entities/entity.h"

/**
 * @brief Třída reprezentující kružnici.
 *
 * Kružnice je definována svým středem a poloměrem.
 */
class Circle final : public Entity {
public:
    /**
     * @brief Vytvoří kružnici.
     * @param center Střed kružnice.
     * @param radius Poloměr kružnice (musí být > 0, kontrola probíhá v parseru).
     */
    Circle(const Point& center, const double radius);

    /**
     * @brief Posune kružnici o daný vektor.
     * Aplikuje se pouze na střed kružnice. Poloměr zůstává nezměněn.
     * @param offset Vektor posunu (dx, dy).
     */
    void translate(const Point& offset) override;

    /**
     * @brief Otočí kružnici kolem zadaného bodu.
     *
     * @note Protože je kružnice rotačně symetrická, rotace mění pouze
     * polohu jejího středu. Samotný tvar ani orientace se vizuálně nemění.
     *
     * @param center Střed rotace (pivot point).
     * @param angle_deg Úhel ve stupních.
     */
    void rotate(const Point& center, const double angle_deg) override;

    /**
     * @brief Přeškáluje kružnici.
     *
     * Tato operace ovlivní dvě vlastnosti:
     * 1. Poloha středu se přiblíží/oddálí od středu škálování.
     * 2. Poloměr se vynásobí faktorem.
     *
     * @param center Střed škálování.
     * @param factor Faktor zvětšení.
     */
    void scale(const Point& center, const double factor) override;

    /**
     * @brief Vykreslí kružnici.
     * Zavolá `renderer.drawCircle(*this)`.
     * @param renderer Použitý renderer.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Getter pro střed kružnice.
     * @return Konstantní reference na bod středu.
     */
    [[nodiscard]] const Point& getCenter() const { return m_center; }

    /**
     * @brief Getter pro poloměr.
     * @return Poloměr jako double.
     */
    [[nodiscard]] double getRadius() const { return m_radius; }

private:
    Point m_center;
    double m_radius;
};

#endif