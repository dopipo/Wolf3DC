#include "code_analyzer.h"
#include "ui.h"
#include <sstream>
#include <regex>

CodeAnalyzer::CodeAnalyzer() : logger(Logger::getInstance()) {}

CodeAnalyzer::~CodeAnalyzer() {}

void CodeAnalyzer::analyze(const std::string& code) {
    logger.info("Starting code analysis...");
    
    metrics = CodeMetrics();  // Reset
    issues.clear();
    
    countLines(code);
    findFunctions(code);
    findVariables(code);
    detectComplexity(code);
    checkForIssues(code);
    
    logger.info("Code analysis completed");
}

const CodeMetrics& CodeAnalyzer::getMetrics() const {
    return metrics;
}

const std::vector<Issue>& CodeAnalyzer::getIssues() const {
    return issues;
}

void CodeAnalyzer::countLines(const std::string& code) {
    metrics.lines = std::count(code.begin(), code.end(), '\n') + 1;
    metrics.comments = 0;
    
    std::istringstream iss(code);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.find("//") != std::string::npos || line.find("/*") != std::string::npos) {
            metrics.comments++;
        }
    }
}

void CodeAnalyzer::findFunctions(const std::string& code) {
    std::regex funcRegex(R"(\w+\s+\w+\s*\([^)]*\)\s*\{)");
    auto begin = std::sregex_iterator(code.begin(), code.end(), funcRegex);
    auto end = std::sregex_iterator();
    metrics.functions = std::distance(begin, end);
}

void CodeAnalyzer::findVariables(const std::string& code) {
    std::regex varRegex(R"((int|char|float|double|void|struct)\s+\w+)");
    auto begin = std::sregex_iterator(code.begin(), code.end(), varRegex);
    auto end = std::sregex_iterator();
    metrics.variables = std::distance(begin, end);
}

void CodeAnalyzer::detectComplexity(const std::string& code) {
    metrics.loops = std::count(code.begin(), code.end(), 'f') + std::count(code.begin(), code.end(), 'w');  // Rough
    metrics.conditionals = std::count(code.begin(), code.end(), 'i') + std::count(code.begin(), code.end(), 'e');  // if/else
    metrics.complexity = metrics.conditionals + metrics.loops + 1;
}

void CodeAnalyzer::checkForIssues(const std::string& code) {
    // Проверка на потенциальные проблемы
    if (metrics.complexity > 10) {
        issues.push_back({"WARNING", "High cyclomatic complexity (" + std::to_string(metrics.complexity) + ")", 0});
    }
    
    if (metrics.lines > 1000) {
        issues.push_back({"INFO", "Large file (" + std::to_string(metrics.lines) + " lines)", 0});
    }
    
    // Проверка на памятьуходы
    if (code.find("malloc") != std::string::npos && code.find("free") == std::string::npos) {
        issues.push_back({"WARNING", "malloc() without free() - potential memory leak", 0});
    }
}

void CodeAnalyzer::printAnalysisReport() const {
    std::cout << "\n";
    UI::printStep(0, "Code Analysis Report");
    UI::printStatsHeader();
    UI::printStats("Total lines", std::to_string(metrics.lines));
    UI::printStats("Functions found", std::to_string(metrics.functions));
    UI::printStats("Variables declared", std::to_string(metrics.variables));
    UI::printStats("Loops detected", std::to_string(metrics.loops));
    UI::printStats("Conditionals", std::to_string(metrics.conditionals));
    UI::printStats("Code comments", std::to_string(metrics.comments));
    UI::printStats("Cyclomatic complexity", std::to_string(metrics.complexity));
    UI::printStatsFooter();
}

void CodeAnalyzer::printComplexityWarnings() const {
    if (issues.empty()) {
        UI::printSuccess("No issues found");
        return;
    }
    
    std::cout << "\n";
    for (const auto& issue : issues) {
        if (issue.severity == "ERROR") {
            UI::printError(issue.message);
        } else if (issue.severity == "WARNING") {
            UI::printWarning(issue.message);
        } else {
            UI::printInfo(issue.message);
        }
    }
}
