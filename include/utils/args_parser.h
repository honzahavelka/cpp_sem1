#ifndef SEM_1_V2_ARGS_PARSER_H
#define SEM_1_V2_ARGS_PARSER_H

#include <string>
#include <vector>


/**
 * @brief Třída pro zpracování a validaci argumentů příkazové řádky.
 *
 * Tato třída se stará o parsování vstupních parametrů aplikace (argc, argv).
 * Provádí kontrolu existence vstupního souboru, validaci formátu výstupního souboru
 * a parsování rozměrů plátna. V případě chyby vyhazuje výjimky.
 */
class ArgsParser {
public:
    /**
     * @brief Struktura držící zvalidovanou konfiguraci aplikace.
     * Slouží jako přepravka dat pro zbytek programu.
     */
    struct Config {
        std::string input_file;
        std::string output_file;
        int width;
        int height;
        std::string format;             ///< Detekovaný formát výstupu ("pgm" nebo "svg").
    };

    /**
     * @brief Konstruktor parseru. Okamžitě provádí validaci všech argumentů.
     *
     * Pokud jsou argumenty v pořádku, naplní se interní struktura Config.
     * Pokud je cokoliv špatně (počet argumentů, nevalidní soubor, špatné rozměry),
     * je vyhozena výjimka.
     *
     * @param argc Počet argumentů příkazové řádky.
     * @param argv Pole argumentů příkazové řádky.
     * @throws std::runtime_error Pokud argumenty nesplňují požadavky zadání.
     */
    ArgsParser(const int argc, char* argv[]);

    /**
     * @brief Vrací připravenou konfiguraci.
     * @return Konstantní reference na strukturu Config s validními daty.
     */
    const Config& getConfig() const { return m_config; }

private:
    Config m_config;        ///< Interní úložiště konfigurace.

    /**
     * @brief Ověří platnost vstupního souboru.
     * Kontroluje příponu .txt, existenci souboru a nepovolené znaky v cestě.
     * @param path Cesta k souboru.
     * @throws std::runtime_error Pokud soubor neexistuje nebo má špatný název.
     */
    void validateInputFile(const std::string& path) const;

    /**
     * @brief Ověří platnost výstupního souboru a detekuje formát.
     * Kontroluje příponu .pgm nebo .svg a nepovolené znaky.
     * Zároveň nastaví položku format v m_config.
     * @param path Cesta k souboru.
     * @throws std::runtime_error Pokud má soubor nepodporovanou příponu.
     */
    void validateOutputFile(const std::string& path);

    /**
     * @brief Naparsuje rozměry plátna z řetězce (např. "800x600").
     * @param size_str Řetězec obsahující rozměry.
     * @throws std::runtime_error Pokud formát neodpovídá "WxH" nebo jsou rozměry záporné.
     */
    void parseCanvasSize(const std::string& size_str);

    /**
     * @brief Pomocná metoda pro kontrolu zakázaných znaků v cestě k souboru.
     * @param path Kontrolovaný řetězec.
     * @param context Název kontextu pro chybovou hlášku (např. "Vstupní soubor").
     * @throws std::runtime_error Pokud řetězec obsahuje znaky jako / \ : * ? " < > |
     */
    void checkInvalidChars(const std::string& path, const std::string& context) const;
};

#endif