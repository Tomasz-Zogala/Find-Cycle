#include<list>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
#include<sstream> 
#include<algorithm> 
#include<set> 
#include "DirectedGraph.h"

int main(int argc, char* argv[])
{
    std::string inputFile;
    std::string outputFile;
    if (argc <= 1) {
        std::cout << "Find cycles in a directed graph" << std::endl;
        std::cout << "-g - name of the input file with graph in format 1 -> 2, 2 -> 3, 3 -> 1" << std::endl;
        std::cout << "-c - name of the output file" << std::endl;
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        if (arg == "-g") {
            ++i;
            if (i == argc) {
                std::cout << "Missing input file name" << std::endl;
                return 1;
            }
            inputFile = std::string(argv[i]);
            continue;
        }
        if (arg == "-c") {
            if (i + 1 == argc) {
                std::cout << "Missing output file name" << std::endl;
                return 1;
            }
            ++i;
            outputFile = std::string(argv[i]);
            continue;
        }
        std::cout << "Unknown argument: " << arg << std::endl;
    }

    if (inputFile.empty()) {
        std::cout << "Missing input file";
        return 1;
    }
    if (outputFile.empty()) {
        std::cout << "Missing output file";
        return 1;
    }

    execute(inputFile, outputFile);

    return 0;
}
