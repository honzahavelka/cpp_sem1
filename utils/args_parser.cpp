#include <iostream>
#include <filesystem>

#include "args_parser.h"

void printInvArgs(int argc) {
    std::cout << "Error: Incorrect number of arguments provided." << std::endl;
    std::cout << "Expected 3 arguments, but received " << argc - 1 << "." << std::endl;
    std::cout << "Usage: drawing.exe <input_file> <output_file> <size>" << std::endl;
    std::cout << "Example: drawing.exe house.txt house.pgm 150x150" << std::endl;
}

void printInvInputFile() {
    std::cout << "Invalid input file." << std::endl;
    std::cout << "Rules for input file:" << std::endl;
    std::cout << "  - Must exist" << std::endl;
    std::cout << "  - Must have .txt extension" << std::endl;
    std::cout << "  - Must not contain characters: / \\ : * ? \" < > |" << std::endl;
}

void printInvOutputFile() {
    std::cout << "Invalid output file." << std::endl;
    std::cout << "Rules for output file:" << std::endl;
    std::cout << "  - Must have .svg or .pgm extension" << std::endl;
    std::cout << "  - Must not contain characters: / \\ : * ? \" < > |" << std::endl;
}

void printInvCanvas() {
    std::cout << "Invalid canvas size." << std::endl;
    std::cout << "Rules for canvas size:" << std::endl;
    std::cout << "  - must declare both sides" << std::endl;
    std::cout << "  - both sides must be greater than 0" << std::endl;
    std::cout << "  - sides are split by \"x\"" << std::endl;
}

bool validInputFile(const std::string &inputFile) {
    /* ends with .txt*/
    if (inputFile.size() < 4 || inputFile.substr(inputFile.size() - 4) != ".txt") {
        std::cout << "Error: Input file " << inputFile <<  " does not have .txt extension." << std::endl;
        return false;
    }

    /* doesnt contain invalid chars*/
    const std::string invalidChars = "/\\:*?\"<>|";
    for (char c : inputFile) {
        if (invalidChars.find(c) != std::string::npos) {
            std::cout << "Error: Input file " << inputFile <<  " contains invalid character " << c << "." << std::endl;
            return false;
        }
    }

    /* exists */
    if (!std::filesystem::exists(inputFile)) {
        std::cout << "Error: Input file " << inputFile <<  " does not exist." << std::endl;
        return false;
    }

    return true;
}

bool validOutputFile(const std::string &outputFile) {
    /* ends with .svg or .pmg*/
    if (outputFile.size() < 4 || outputFile.substr(outputFile.size() - 4) != ".svg" && outputFile.substr(outputFile.size() - 4) != ".pgm") {
        std::cout << "Error: Output file " << outputFile <<  " does not have .svg or .pgm extension." << std::endl;
        return false;
    }

    /* doesnt contain invalid chars*/
    const std::string invalidChars = "/\\:*?\"<>|";
    for (char c : outputFile) {
        if (invalidChars.find(c) != std::string::npos) {
            std::cout << "Error: Output file " << outputFile <<  " contains invalid character " << c << "." << std::endl;
            return false;
        }
    }

    return true;
}

bool validCanvasSize(const std::string &canvasSize, int& width, int& height) {
    /* find x pos */
    size_t xpos = canvasSize.find('x');
    if (xpos == std::string::npos) {
        std::cout << "Error: canvas size " << canvasSize << " does not contain both sides." << std::endl;
        return false;
    }

    std::string x = canvasSize.substr(0, xpos);
    std::string y = canvasSize.substr(xpos + 1);

    if (x.empty() || y.empty()) {
        std::cout << "Error: canvas size " << canvasSize << " does not contain both sides." << std::endl;
        return false;
    }

    try {
        width = std::stoi(x);
        height = std::stoi(y);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: width and height must be an integer value in " << canvasSize << "." << std::endl;
        return false;
    }

    if (width <= 0 || height <= 0) {
        std::cout << "Error: width and height must be greater than 0 in " << canvasSize << "." << std::endl;
        return false;
    }
    return true;
}