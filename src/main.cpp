#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

int main(int argc, char* argv[]) {
    // Инициализация логгера
    Logger& logger = Logger::getInstance();
    if (!logger.initialize("w3d_compiler.log")) {
        std::cerr << "Warning: Could not initialize file logging" << std::endl;
        logger.setConsoleOutput(true);
        logger.setFileOutput(false);
    } else {
        logger.info("Logger initialized - w3d_compiler.log");
        logger.setFileOutput(true);
    }
    
    if (argc < 3) {
        std::cout << "W3D Compiler - Wolfenstein 3D C to C++ Compiler\n";
        std::cout << "Usage: w3d_compiler <input.c> <output.cpp> [options]\n\n";
        std::cout << "Options:\n";
        std::cout << "  --target dos         Compile for DOS\n";
        std::cout << "  --target android     Compile for Android\n";
        std::cout << "  --mode real          DOS real mode (16-bit)\n";
        std::cout << "  --mode protected     DOS protected mode (32-bit)\n";
        std::cout << "  --vesa               Enable VESA video support (DOS)\n";
        std::cout << "  --arch arm           Android ARM architecture\n";
        std::cout << "  --arch arm64         Android ARM64 architecture\n";
        std::cout << "  --optimize O2        Optimization level (O0-O3, Os)\n";
        logger.warning("Insufficient command line arguments");
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::string target = "native";
    std::string dosMode = "protected";
    std::string androidArch = "arm64";
    std::string optimLevel = "O2";
    bool useVesa = false;

    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--target") == 0 && i + 1 < argc) {
            target = argv[++i];
        }
        else if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
            dosMode = argv[++i];
        }
        else if (strcmp(argv[i], "--arch") == 0 && i + 1 < argc) {
            androidArch = argv[++i];
        }
        else if (strcmp(argv[i], "--vesa") == 0) {
            useVesa = true;
        }
        else if (strcmp(argv[i], "--optimize") == 0 && i + 1 < argc) {
            optimLevel = argv[++i];
        }
    }

    Compiler compiler;

    std::cout << "W3D Compiler v1.0\n";
    std::cout << "Input:  " << inputFile << "\n";
    std::cout << "Output: " << outputFile << "\n";
    std::cout << "Target: " << target << "\n";
    
    logger.infof("Input: %s", inputFile.c_str());
    logger.infof("Output: %s", outputFile.c_str());
    logger.infof("Target: %s", target.c_str());

    if (target == "dos") {
        std::cout << "DOS Mode: " << dosMode << "\n";
        logger.infof("DOS Mode: %s", dosMode.c_str());
        if (useVesa) {
            std::cout << "VESA: Enabled\n";
            logger.info("VESA: Enabled");
        }
    }
    else if (target == "android") {
        std::cout << "Android Arch: " << androidArch << "\n";
        logger.infof("Android Arch: %s", androidArch.c_str());
    }

    std::cout << "Optimization: " << optimLevel << "\n";
    logger.infof("Optimization: %s", optimLevel.c_str());
    std::cout << "\nCompiling...\n";
    logger.info("Starting compilation process...");

    if (compiler.compile(inputFile, outputFile)) {
        std::cout << "Compilation successful!\n";
        logger.info("===== COMPILATION SUCCESSFUL =====");
        return 0;
    }
    else {
        std::cerr << "Compilation failed!\n";
        logger.critical("===== COMPILATION FAILED =====");
        return 1;
    }
}
