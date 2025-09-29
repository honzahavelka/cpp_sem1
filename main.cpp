#include <iostream>

#include "args_parser.h"

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
    /* check output file */
    if (!validOutputFile(argv[2])) {
        printInvOutputFile();
        return 3;
    }

    /* check canvas */
    int width, height;
    if (!validCanvasSize(argv[3], width, height)) {
        printInvCanvas();
        return 4;
    }





    /*  exit codes:
     *  0 - success
     *  1 - invalid arguments
     *  2 - invalid input file
     *  3 - invalid output file
     *  4 - invalid canvas size
     *  5 - invalid commands in input file
     *  6 - unexpected error
     */

    return 0;
}