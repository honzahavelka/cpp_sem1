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

    Canvas canvas(width, height);
    Parser parser(inputFile);

    if (!parser.parseFile()) {
        std::cout << "Failed to parse file: " << inputFile << std::endl;
        return 5;
    }

    auto& commands = parser.getCommands();
    for (auto& cmd : commands) {
        cmd->execute(canvas);
    }

    Renderer::SVGRender(canvas, outputFile);

    /*  exit codes:
     *  0 - success
     *  1 - invalid arguments
     *  2 - invalid input file
     *  3 - invalid output file
     *  4 - invalid canvas size
     *  5 - invalid commands in input file
     *  6 - unexpected error
     */
    std::cout << "OK" << std::endl;
    std::cout << parser.getCommandsCount() << std::endl;
    return 0;
}
