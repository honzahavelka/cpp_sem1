#ifndef SEM_1_V2_POINT_H
#define SEM_1_V2_POINT_H

#include <valarray>

/**
 * @brief Struktura reprezentující bod nebo vektor ve 2D prostoru.
 * * Tato struktura slouží jako základní stavební kámen pro veškerou geometrii.
 * Obsahuje přetížené operátory pro vektorovou aritmetiku, což zjednodušuje
 * zápis transformací.
 */
struct Point {
    double x;
    double y;

    /**
     * @brief Sečte dva body (vektorový součet).
     * Slouží primárně pro translaci (posun) bodu o daný vektor.
     * @param other Druhý bod (vektor posunu).
     * @return Nový bod vzniklý součtem souřadnic.
     */
    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    /**
     * @brief Odečte jeden bod od druhého (vektorový rozdíl).
     * Slouží k získání vektoru směru mezi dvěma body nebo k posunu opačným směrem.
     * @param other Bod, který odčítáme.
     * @return Nový bod (vektor) vzniklý rozdílem souřadnic.
     */
    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }

    /**
     * @brief Vynásobí souřadnice skalárem.
     * Slouží pro škálování (zvětšování/zmenšování) vzdáleností.
     * @param factor Číslo, kterým násobíme (faktor škálování).
     * @return Nový bod s přenásobenými souřadnicemi.
     */
    Point operator*(const double factor) const {
        return {x * factor, y * factor};
    }

    /**
     * @brief Otočí bod kolem zadaného středu o daný úhel.
     * * Metoda převede bod do lokálního souřadného systému středu,
     * provede rotaci pomocí rotační matice a vrátí bod zpět do globálních souřadnic.
     *
     * @param center Střed rotace (pivot).
     * @param angle Úhel rotace v RADIÁNECH.
     * @return Nový bod po rotaci.
     */
    [[nodiscard]] Point rotateAround(const Point& center, const double angle) const {
        const double s = std::sin(angle);
        const double c = std::cos(angle);

        // posun do počátku souřadnic
        const Point shift = *this - center;

        // aplikace rotace
        const double new_x = c * shift.x - s * shift.y;
        const double new_y = s * shift.x + c * shift.y;

        // posun zpět na svoje místo
        return {new_x + center.x, new_y + center.y};
    }
};

#endif