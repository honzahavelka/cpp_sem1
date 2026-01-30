#ifndef SEM_1_V2_COMMAND_PARSER_H
#define SEM_1_V2_COMMAND_PARSER_H

#include "entities/entity.h"

#include <vector>
#include <string>
#include <memory>

/**
 * @brief Třída odpovědná za parsování textových příkazů a vytváření grafických objektů.
 *
 * CommandParser čte vstupní soubor řádek po řádku, interpretuje příkazy
 * a podle nich buď vytváří nové instance třídy Entity, nebo modifikuje ty stávající.
 */
class CommandParser {
public:
    /**
     * @brief Hlavní metoda pro zpracování vstupního souboru.
     *
     * Otevře soubor, projde ho řádek po řádku a vygeneruje seznam entit.
     * Pokud narazí na chybu syntaxe, vyhodí výjimku obalenou informací o číslu řádku.
     *
     * @param filename Cesta ke vstupnímu souboru s příkazy.
     * @return Vektor unikátních ukazatelů na vytvořené entity.
     * Předává vlastnictví objektů volajícímu.
     * @throws std::runtime_error Pokud nelze otevřít soubor nebo obsahuje chyby.
     */
    std::vector<std::unique_ptr<Entity>> parse(const std::string& filename);

    /**
     * @brief Vrací celkový počet úspěšně zpracovaných příkazů.
     * Slouží pro statistické výpisy na konci program.
     * @return Počet příkazů.
     */
    [[nodiscard]] int getNumberOfCommands() const { return m_number_of_commands; }

private:
    int m_current_line = 0;                             ///< Aktuální číslo řádku (pro chybové výpisy).
    int m_number_of_commands = 0;                       ///< Počítadlo validních příkazů.

    /**
     * @brief Dočasné úložiště entit během parsování.
     * Parser si zde drží entity, aby na ně mohl aplikovat hromadné
     * transformace ještě předtím, než je vrátí.
     */
    std::vector<std::unique_ptr<Entity>> m_entities;

    /**
     * @brief Zpracuje jeden konkrétní řádek textu.
     * Rozpozná klíčové slovo a provede příslušnou akci.
     * @param line Řádek textu k parsování.
     * @throws std::runtime_error Při neznámém příkazu nebo špatných parametrech.
     */
    void processLine(const std::string& line);

    /**
     * @brief Odstraní komentáře z řádku.
     * Hledá znak '#' a ořízne vše za ním.
     *
     * @param line Vstupní řádek.
     * @return Řádek bez komentáře a přebytečných mezer.
     */
    [[nodiscard]] std::string stripComment(const std::string& line) const;
};

#endif