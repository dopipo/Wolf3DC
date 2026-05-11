#ifndef INTERACTIVE_SHELL_H
#define INTERACTIVE_SHELL_H

#include <string>
#include <memory>
#include "compiler.h"
#include "code_analyzer.h"
#include "optimizer.h"
#include "logger.h"

class InteractiveShell {
public:
    InteractiveShell();
    ~InteractiveShell();
    
    // Запустить интерактивную оболочку
    void run();
    
private:
    std::unique_ptr<Compiler> compiler;
    std::unique_ptr<CodeAnalyzer> analyzer;
    std::unique_ptr<Optimizer> optimizer;
    Logger& logger;
    
    // Команды
    void handleCommand(const std::string& command);
    void showHelp();
    void showMenu();
    void compileFile();
    void analyzeFile();
    void optimizeFile();
    void showSettings();
    void showAbout();
    
    // Утилиты
    std::string trim(const std::string& str);
    std::vector<std::string> splitCommand(const std::string& cmd);
};

#endif // INTERACTIVE_SHELL_H
