#include "parser/command_parser.h"
#include "renderers/pgm_renderer.h"
#include "renderers/svg_renderer.h"
#include "utils/args_parser.h"

#include <iostream>
#include <memory>

int main(const int argc, char* argv[]) {
    try {
        const ArgsParser parser(argc, argv);
        const auto& config = parser.getConfig();

        CommandParser cmd_parser;
        const auto entities = cmd_parser.parse(config.input_file);

        std::unique_ptr<Renderer> renderer;
        if (config.format == "svg") {
            renderer = std::make_unique<SvgRenderer>(config.output_file, config.width, config.height);
        } else {
            renderer = std::make_unique<PgmRenderer>(config.output_file, config.width, config.height);
        }

        for (const auto& entity : entities) {
            entity->draw(*renderer);
        }

        renderer->save();

        std::cout << "OK" << std::endl;
        std::cout << cmd_parser.getNumberOfCommands() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}