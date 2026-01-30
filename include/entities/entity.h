#ifndef SEM_1_V2_ENTITY_H
#define SEM_1_V2_ENTITY_H

#include "utils/point.h"

// forward deklarace pro zamezaní cyklické závislosti
class Renderer;

/**
 * @brief Abstraktní bázová třída reprezentující libovolný grafický objekt.
 *
 * Tato třída definuje společné rozhraní, které musí implementovat
 * všechny konkrétní tvary. Díky tomu můžeme s různými
 * tvary pracovat jednotně pomocí polymorfismu.
 */
class Entity {
public:
    /**
     * @brief Virtuální destruktor.
     * Nezbytný pro správné uvolnění paměti, když mažeme objekty přes pointer na Entity.
     */
    virtual ~Entity() = default;

    /**
     * @brief Posune entitu o zadaný vektor.
     * @param offset Vektor posunu (dx, dy), který se přičte k souřadnicím entity.
     */
    virtual void translate(const Point& offset) = 0;

    /**
     * @brief Otočí entitu kolem zadaného středu.
     *
     * @note Metoda očekává úhel ve STUPNÍCH. Implementace v potomcích
     * by měla provést převod na radiány.
     *
     * @param center Bod, kolem kterého se rotace provádí (pivot).
     * @param angle_deg Úhel rotace ve stupních (kladný = po směru hodinových ručiček).
     */
    virtual void rotate(const Point& center, const double angle_deg) = 0;

    /**
     * @brief Přeškáluje entitu vzhledem k zadanému středu.
     * @param center Střed, vůči kterému se škáluje.
     * @param factor Faktor škálování: 1.0 = beze změny, >1.0 = zvětšení, <1.0 = zmenšení.
     */
    virtual void scale(const Point& center, const double factor) = 0;

    /**
     * @brief Vykreslí entitu pomocí předaného rendereru.
     *
     * Entita použije renderer a zavolá jeho specifickou metodu pro svůj typ
     * (např. `renderer.drawCircle(*this)`).
     *
     * @param renderer Reference na renderer, který provede samotné vykreslení.
     */
    virtual void draw(Renderer& renderer) const = 0;
};

#endif