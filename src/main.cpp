#include "parser/command_parser.h"
#include "renderers/pgm_renderer.h"
#include "renderers/svg_renderer.h"
#include "utils/args_parser.h"

#include <iostream>
#include <memory>

/**
 * @file main.cpp
 * @author Jan Havelka
 * @brief 1. semestrální práce z KIV/CPP
 * @date 2026-01-29
 *
 * Aplikace načítá příkazy ze souboru a generuje SVG nebo PGM obrázek.
 */

int main(const int argc, char* argv[]) {
    // obalení do try catch
    // jakákoliv chyba vybublá sem jako výjimka, kterou program vypíše
    try {
        // zpracování argumentů v konstruktoru
        const ArgsParser parser(argc, argv);
        const auto& config = parser.getConfig();

        // parsování vstupního souboru
        // parse() vrátí vektor unikátních pointerů std::unique_ptr<Entity>
        // -> přebereme vlastníctví
        CommandParser cmd_parser;
        const auto entities = cmd_parser.parse(config.input_file);

        // výběr rendereru
        std::unique_ptr<Renderer> renderer;
        if (config.format == "svg") {
            renderer = std::make_unique<SvgRenderer>(config.output_file, config.width, config.height);
        } else {
            renderer = std::make_unique<PgmRenderer>(config.output_file, config.width, config.height);
        }

        // projdeme všechny entity a každá zavolá a předá sama sebe vybranému rendereru.
        for (const auto& entity : entities) {
            entity->draw(*renderer);
        }

        // uložení do souboru
        renderer->save();

        // výpis úspěchu a zadání
        std::cout << "OK" << std::endl;
        std::cout << cmd_parser.getNumberOfCommands() << std::endl;

    } catch (const std::exception& e) {
        // pokud nastala chyba, vypíšeme ji a vrátíme chybový kód.
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}