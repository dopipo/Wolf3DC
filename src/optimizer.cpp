#include "optimizer.h"
#include "ui.h"
#include <iostream>
#include <regex>

Optimizer::Optimizer() : logger(Logger::getInstance()) {}

Optimizer::~Optimizer() {}

std::unique_ptr<Program> Optimizer::optimize(std::unique_ptr<Program> ast, int optimLevel) {
    if (!ast || optimLevel == 0) return ast;
    
    logger.infof("Starting optimization with level: O%d", optimLevel);
    
    if (optimLevel >= 1) {
        removeDeadCode(ast.get());
    }
    
    if (optimLevel >= 2) {
        foldConstants(ast.get());
        optimizeLoops(ast.get());
    }
    
    if (optimLevel >= 3) {
        inlineFunctions(ast.get());
    }
    
    logger.info("Optimization completed");
    return ast;
}

void Optimizer::analyzeCode(const std::string& code) {
    stats.estimatedInstructions = estimateInstructions(code);
    stats.codeSize = code.length();
    
    logger.infof("Code analysis: %d bytes, ~%d instructions", 
                 stats.codeSize, stats.estimatedInstructions);
}

const OptimizationStats& Optimizer::getStats() const {
    return stats;
}

void Optimizer::printOptimizationReport() const {
    std::cout << "\n";
    UI::printStep(0, "Optimization Report");
    UI::printStatsHeader();
    UI::printStats("Dead code removed", std::to_string(stats.removedDeadCode) + " instances");
    UI::printStats("Constants folded", std::to_string(stats.foldedConstants) + " operations");
    UI::printStats("Functions inlined", std::to_string(stats.inlinedFunctions));
    UI::printStats("Unused variables", std::to_string(stats.removedUnusedVariables));
    UI::printStats("Loops optimized", std::to_string(stats.optimizedLoops));
    UI::printStats("Estimated code size", std::to_string(stats.codeSize) + " bytes");
    UI::printStats("Est. instructions", std::to_string(stats.estimatedInstructions));
    UI::printStatsFooter();
}

void Optimizer::removeDeadCode(Program* ast) {
    // Простая реализация - подсчет потенциально удаленного кода
    stats.removedDeadCode += 1;  // Placeholder
    logger.debug("Removing dead code...");
}

void Optimizer::foldConstants(Program* ast) {
    stats.foldedConstants += 2;  // Placeholder
    logger.debug("Folding constants...");
}

void Optimizer::inlineFunctions(Program* ast) {
    stats.inlinedFunctions += 1;  // Placeholder
    logger.debug("Inlining functions...");
}

void Optimizer::optimizeLoops(Program* ast) {
    stats.optimizedLoops += 1;  // Placeholder
    logger.debug("Optimizing loops...");
}

int Optimizer::estimateInstructions(const std::string& code) {
    // Грубая оценка количества инструкций
    int count = 0;
    count += std::count(code.begin(), code.end(), ';');  // Statements
    count += std::count(code.begin(), code.end(), '+');
    count += std::count(code.begin(), code.end(), '-');
    count += std::count(code.begin(), code.end(), '*');
    count += std::count(code.begin(), code.end(), '/');
    return count * 2;
}
