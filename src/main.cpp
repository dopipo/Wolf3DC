#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include "logger.h"
#include "ui.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

int main(int argc, char* argv[]) {
    // Инициализация UI
    UI::printHeader();
    
    // Инициализация логгера
    Logger& logger = Logger::getInstance();
    if (!logger.initialize("w3d_compiler.log")) {
        UI::printWarning("Could not initialize file logging");
        logger.setConsoleOutput(true);
        logger.setFileOutput(false);
    } else {
        UI::printSuccess("Logger initialized - w3d_compiler.log");
        logger.info("Logger initialized - w3d_compiler.log");
        logger.setFileOutput(true);
    }
    
    // Проверка аргументов
    if (argc < 3) {
        std::cout << "\n";
        UI::printInfo("Usage: w3d_compiler <input.c> <output.cpp> [options]\n");
        
        std::cout << "\nOptions:\n";
        std::cout << "  --target dos         Compile for DOS\n";
        std::cout << "  --target android     Compile for Android\n";
        std::cout << "  --mode real          DOS real mode (16-bit)\n";
        std::cout << "  --mode protected     DOS protected mode (32-bit)\n";
        std::cout << "  --vesa               Enable VESA video support (DOS)\n";
        std::cout << "  --arch arm           Android ARM architecture\n";
        std::cout << "  --arch arm64         Android ARM64 architecture\n";
        std::cout << "  --optimize O0|O1|O2|O3|Os  Optimization level\n";
        std::cout << "\nExample:\n";
        std::cout << "  w3d_compiler game.c game.cpp --target dos --mode protected\n\n";
        
        logger.warning("Insufficient command line arguments");
        UI::printFooter();
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::string target = "native";
    std::string dosMode = "protected";
    std::string androidArch = "arm64";
    std::string optimLevel = "O2";
    bool useVesa = false;

    // Парсинг опций
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

    // Вывод конфигурации
    std::cout << "\n";
    UI::printStatsHeader();
    UI::printStats("Input file", inputFile);
    UI::printStats("Output file", outputFile);
    UI::printStats("Target platform", target);
    
    if (target == "dos") {
        UI::printStats("DOS Mode", dosMode);
        if (useVesa) {
            UI::printStats("VESA Support", "Enabled");
        }
    }
    else if (target == "android") {
        UI::printStats("Android Architecture", androidArch);
    }
    
    UI::printStats("Optimization", optimLevel);
    UI::printStatsFooter();
    
    logger.infof("Configuration - Input: %s, Output: %s, Target: %s", inputFile.c_str(), outputFile.c_str(), target.c_str());
    logger.infof("Optimization level: %s", optimLevel.c_str());

    std::cout << "\n";
    UI::printInfo("Starting compilation process...");
    logger.info("Starting compilation process...");

    // Запуск компиляции
    if (compiler.compile(inputFile, outputFile)) {
        std::cout << "\n";
        logger.info("===== COMPILATION SUCCESSFUL =====");
        UI::printFooter();
        return 0;
    }
    else {
        std::cout << "\n";
        UI::printError("Compilation failed! Check w3d_compiler.log for details");
        logger.critical("===== COMPILATION FAILED =====");
        UI::printFooter();
        return 1;
    }
}
