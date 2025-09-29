#include <iostream>

int main(int argc, const char** argv) {

    /* sanity check */
    if (argc != 4) {
        std::cout << "Error: Incorrect number of arguments provided." << std::endl;
        std::cout << "Expected 3 arguments, but received " << argc - 1 << "." << std::endl;
        std::cout << "Usage: drawing.exe <input_file> <output_file> <size>" << std::endl;
        std::cout << "Example: drawing.exe house.txt house.pgm 150x150" << std::endl;
        return 1;
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