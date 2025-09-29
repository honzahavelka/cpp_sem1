#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

void printInvArgs(int argc);
void printInvInputFile();
void printInvOutputFile();
void printInvCanvas();

bool validInputFile(const std::string& inputFile);
bool validOutputFile(const std::string& outputFile);
bool validCanvasSize(const std::string& canvasSize, int& width, int& height);

#endif
