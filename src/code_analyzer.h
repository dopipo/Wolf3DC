#ifndef CODE_ANALYZER_H
#define CODE_ANALYZER_H

#include <string>
#include <vector>
#include <map>
#include "logger.h"

struct CodeMetrics {
    int lines = 0;
    int functions = 0;
    int variables = 0;
    int loops = 0;
    int conditionals = 0;
    int comments = 0;
    int complexity = 0;  // Cyclomatic complexity
};

struct Issue {
    std::string severity;  // "INFO", "WARNING", "ERROR"
    std::string message;
    int line = 0;
};

class CodeAnalyzer {
public:
    CodeAnalyzer();
    ~CodeAnalyzer();
    
    // Анализ кода
    void analyze(const std::string& code);
    
    // Получить метрики
    const CodeMetrics& getMetrics() const;
    
    // Получить проблемы
    const std::vector<Issue>& getIssues() const;
    
    // Печать отчета
    void printAnalysisReport() const;
    void printComplexityWarnings() const;
    
private:
    CodeMetrics metrics;
    std::vector<Issue> issues;
    Logger& logger;
    
    // Методы анализа
    void countLines(const std::string& code);
    void findFunctions(const std::string& code);
    void findVariables(const std::string& code);
    void detectComplexity(const std::string& code);
    void checkForIssues(const std::string& code);
};

#endif // CODE_ANALYZER_H
