#ifndef COMPILER_PIPELINE_H
#define COMPILER_PIPELINE_H

#include <string>
#include <vector>
#include <memory>

enum class CompilerBackend {
    DJGPP,
    OPEN_WATCOM,
    AUTO_DETECT
};

enum class MemoryModel {
    REAL_MODE,      // 16-bit real mode (64KB segments)
    PROTECTED_MODE  // 32-bit protected mode (CWSDPMI)
};

struct CompileOptions {
    CompilerBackend backend;
    MemoryModel memoryModel;
    std::string outputFile;
    int optimizationLevel;  // 0-3
    bool generateDebugInfo;
    std::string includePaths;
    std::vector<std::string> defines;
};

struct CompileResult {
    bool success;
    std::string executablePath;
    std::string errorLog;
    std::string warningLog;
    int compilationTime; // seconds
    long fileSize;       // bytes
};

class CompilerPipeline {
private:
    CompilerBackend detectedBackend;
    std::string djgppPath;
    std::string watcomPath;

    bool detectCompilers();
    std::string getCompilerCommand(CompilerBackend backend, const CompileOptions& opts);
    CompileResult parseCompilerOutput(const std::string& output);

public:
    CompilerPipeline();
    ~CompilerPipeline();

    bool initialize();
    CompileResult compile(const std::vector<std::string>& sourceFiles, const CompileOptions& options);
    CompileResult compileFile(const std::string& sourceFile, const CompileOptions& options);
    std::string getDOSLinkerScript(MemoryModel model);
};

#endif // COMPILER_PIPELINE_H
