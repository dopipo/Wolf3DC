#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <string>
#include <vector>
#include <memory>
#include "parser.h"
#include "logger.h"

struct OptimizationStats {
    int removedDeadCode = 0;
    int foldedConstants = 0;
    int inlinedFunctions = 0;
    int removedUnusedVariables = 0;
    int optimizedLoops = 0;
    int codeSize = 0;
    int estimatedInstructions = 0;
};

class Optimizer {
public:
    Optimizer();
    ~Optimizer();
    
    // Оптимизация AST
    std::unique_ptr<Program> optimize(std::unique_ptr<Program> ast, int optimLevel);
    
    // Анализ кода
    void analyzeCode(const std::string& code);
    
    // Получить статистику
    const OptimizationStats& getStats() const;
    
    // Отчет об оптимизации
    void printOptimizationReport() const;
    
private:
    OptimizationStats stats;
    Logger& logger;
    
    // Внутренние методы оптимизации
    void removeDeadCode(Program* ast);
    void foldConstants(Program* ast);
    void inlineFunctions(Program* ast);
    void optimizeLoops(Program* ast);
    
    // Анализ
    int estimateInstructions(const std::string& code);
};

#endif // OPTIMIZER_H
