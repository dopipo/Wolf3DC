#include "interactive_shell.h"
#include "ui.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

InteractiveShell::InteractiveShell()
    : compiler(std::make_unique<Compiler>()),
      analyzer(std::make_unique<CodeAnalyzer>()),
      optimizer(std::make_unique<Optimizer>()),
      logger(Logger::getInstance()) {}

InteractiveShell::~InteractiveShell() {}

void InteractiveShell::run() {
    logger.info("Starting interactive shell");
    
    showMenu();
    
    std::string command;
    while (true) {
        std::cout << "\n[W3D] > ";
        std::getline(std::cin, command);
        
        if (command.empty()) continue;
        
        if (command == "exit" || command == "quit") {
            UI::printInfo("Exiting W3D Compiler...");
            logger.info("Interactive shell closed");
            break;
        }
        
        handleCommand(command);
    }
}

void InteractiveShell::handleCommand(const std::string& command) {
    auto tokens = splitCommand(command);
    if (tokens.empty()) return;
    
    std::string cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    if (cmd == "compile" || cmd == "c") {
        compileFile();
    }
    else if (cmd == "analyze" || cmd == "a") {
        analyzeFile();
    }
    else if (cmd == "optimize" || cmd == "o") {
        optimizeFile();
    }
    else if (cmd == "help" || cmd == "h" || cmd == "?") {
        showHelp();
    }
    else if (cmd == "menu" || cmd == "m") {
        showMenu();
    }
    else if (cmd == "settings" || cmd == "s") {
        showSettings();
    }
    else if (cmd == "about") {
        showAbout();
    }
    else {
        UI::printWarning("Unknown command: " + cmd + " (type 'help' for commands)");
        logger.warning("Unknown command: " + cmd);
    }
}

void InteractiveShell::showMenu() {
    UI::printHeader();
    std::cout << "\n";
    UI::printColored("Welcome to W3D Compiler - Interactive Mode", UI::Color::CYAN);
    std::cout << "\n";
    UI::printInfo("Type a command or 'help' for available commands\n");
    
    UI::printColored("Quick Commands:", UI::Color::GREEN);
    std::cout << "  [C]ompile    - Compile C file to C++\n";
    std::cout << "  [A]nalyze    - Analyze code complexity\n";
    std::cout << "  [O]ptimize   - Optimize generated code\n";
    std::cout << "  [M]enu       - Show this menu\n";
    std::cout << "  [H]elp       - Show help\n";
    std::cout << "  [S]ettings   - Show settings\n";
    std::cout << "  exit/quit    - Exit program\n";
}

void InteractiveShell::showHelp() {
    std::cout << "\n";
    UI::printColored("=== W3D COMPILER HELP ===", UI::Color::CYAN);
    std::cout << "\n";
    std::cout << "compile <input.c> <output.cpp> [options]\n";
    std::cout << "  Compile C source file to C++\n";
    std::cout << "  Options: --target dos|android|native\n";
    std::cout << "           --optimize O0|O1|O2|O3|Os\n\n";
    
    std::cout << "analyze <file.c>\n";
    std::cout << "  Analyze code complexity and metrics\n\n";
    
    std::cout << "optimize <file.c> [level]\n";
    std::cout << "  Optimize code (level 0-3, default 2)\n\n";
    
    std::cout << "settings\n";
    std::cout << "  Show/modify compiler settings\n\n";
    
    std::cout << "exit | quit\n";
    std::cout << "  Exit the program\n\n";
}

void InteractiveShell::compileFile() {
    std::string input, output;
    
    std::cout << "\nInput file: ";
    std::getline(std::cin, input);
    input = trim(input);
    
    std::cout << "Output file: ";
    std::getline(std::cin, output);
    output = trim(output);
    
    if (input.empty() || output.empty()) {
        UI::printError("Invalid file paths");
        return;
    }
    
    std::cout << "\n";
    if (compiler->compile(input, output)) {
        logger.infof("Compilation successful: %s -> %s", input.c_str(), output.c_str());
    } else {
        logger.errorf("Compilation failed: %s", input.c_str());
    }
}

void InteractiveShell::analyzeFile() {
    std::string file;
    std::cout << "\nFile to analyze: ";
    std::getline(std::cin, file);
    file = trim(file);
    
    if (file.empty()) {
        UI::printError("Invalid file path");
        return;
    }
    
    std::ifstream ifs(file);
    if (!ifs.is_open()) {
        UI::printError("Cannot open file: " + file);
        logger.error("Cannot open file for analysis: " + file);
        return;
    }
    
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();
    
    std::cout << "\n";
    analyzer->analyze(content);
    analyzer->printAnalysisReport();
    analyzer->printComplexityWarnings();
    
    logger.infof("Analysis complete: %s", file.c_str());
}

void InteractiveShell::optimizeFile() {
    std::string file;
    int level = 2;
    
    std::cout << "\nFile to optimize: ";
    std::getline(std::cin, file);
    file = trim(file);
    
    std::cout << "Optimization level (0-3, default 2): ";
    std::string levelStr;
    std::getline(std::cin, levelStr);
    if (!levelStr.empty()) {
        level = std::stoi(levelStr);
    }
    
    UI::printInfo("Optimization at level " + std::to_string(level) + " enabled");
    logger.infof("Optimization level: %d", level);
}

void InteractiveShell::showSettings() {
    std::cout << "\n";
    UI::printStep(0, "Compiler Settings");
    UI::printStatsHeader();
    UI::printStats("Log file", "w3d_compiler.log");
    UI::printStats("Output format", "C++17");
    UI::printStats("Default target", "native");
    UI::printStats("Default optimization", "O2");
    UI::printStats("Max file size", "10 MB");
    UI::printStatsFooter();
}

void InteractiveShell::showAbout() {
    std::cout << "\n";
    UI::printColored("╔════════════════════════════════════════╗", UI::Color::CYAN);
    UI::printColored("║  W3D COMPILER - Wolfenstein 3D C2C++  ║", UI::Color::CYAN);
    UI::printColored("║         Version 2.0 (Interactive)      ║", UI::Color::CYAN);
    UI::printColored("║                                        ║", UI::Color::CYAN);
    UI::printColored("║  A modern compiler for legacy games    ║", UI::Color::CYAN);
    UI::printColored("║  with advanced analysis & optimization ║", UI::Color::CYAN);
    UI::printColored("║                                        ║", UI::Color::CYAN);
    UI::printColored("║  Features:                             ║", UI::Color::CYAN);
    UI::printColored("║  • Cross-platform compilation          ║", UI::Color::CYAN);
    UI::printColored("║  • Code analysis & metrics             ║", UI::Color::CYAN);
    UI::printColored("║  • Multi-level optimization            ║", UI::Color::CYAN);
    UI::printColored("║  • Interactive shell                   ║", UI::Color::CYAN);
    UI::printColored("║  • Detailed error logging              ║", UI::Color::CYAN);
    UI::printColored("╚════════════════════════════════════════╝", UI::Color::CYAN);
    std::cout << "\n";
}

std::string InteractiveShell::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

std::vector<std::string> InteractiveShell::splitCommand(const std::string& cmd) {
    std::vector<std::string> tokens;
    std::istringstream iss(cmd);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}
