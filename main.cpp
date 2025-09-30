#include <iostream>

#include "utils/args_parser.h"
#include "canvas/canvas.h"
#include "parser/parser.h"
#include "utils/renderer.h"

int main(int argc, const char** argv) {
    /* sanity check */
    if (argc != 4) {
        printInvArgs(argc);
        return 1;
    }
    /* check input file */
    if (!validInputFile(argv[1])) {
        printInvInputFile();
        return 2;
    }
    std::string inputFile = argv[1];

    /* check output file */
    if (!validOutputFile(argv[2])) {
        printInvOutputFile();
        return 3;
    }
    std::string outputFile = argv[2];

    /* check canvas */
    int width, height;
    if (!validCanvasSize(argv[3], width, height)) {
        printInvCanvas();
        return 4;
    }

    /* create canvas and parser */
    Canvas canvas(width, height);
    Parser parser(inputFile);

    /* if parser found mistake in commands, return */
    if (!parser.parseFile()) {
        std::cout << "Failed to parse file: " << inputFile << std::endl;
        return 5;
    }

    /* execute commands on canvas */
    auto& commands = parser.getCommands();
    for (auto& cmd : commands) {
        cmd->execute(canvas);
    }

    /* if svg, render svg, else render pgm */
    if (outputFile.substr(outputFile.size() - 3) == "svg") {
        if (!Renderer::SVGRender(canvas, outputFile)) {
            std::cout << "Error, failed to render SVG file: " << outputFile << std::endl;
            return 3;
        }
    }
    else if (outputFile.substr(outputFile.size() - 3) == "pgm") {
        if (!Renderer::PGMRender(canvas, outputFile)) {
            std::cout << "Error, failed to render PGM file: " << outputFile << std::endl;
            return 3;
        }
    }

    /*  exit codes:
     *  0 - success
     *  1 - invalid arguments
     *  2 - invalid input file
     *  3 - invalid output file
     *  4 - invalid canvas size
     *  5 - invalid commands in input file
     */
    std::cout << "OK" << std::endl;
    std::cout << parser.getCommandsCount() << std::endl;
    return 0;
}
