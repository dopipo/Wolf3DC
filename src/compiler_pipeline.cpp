#include "compiler_pipeline.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>

CompilerPipeline::CompilerPipeline() : detectedBackend(CompilerBackend::AUTO_DETECT) {}

CompilerPipeline::~CompilerPipeline() {}

bool CompilerPipeline::initialize() {
    return detectCompilers();
}

bool CompilerPipeline::detectCompilers() {
    // Try to detect DJGPP
#ifdef _WIN32
    int djgpp_check = system("where djgpp-gcc >nul 2>&1");
    int djgpp_check2 = system("where i586-pc-msdosdjgpp-gcc >nul 2>&1");
#else
    int djgpp_check = system("which djgpp-gcc >/dev/null 2>&1");
    int djgpp_check2 = system("which i586-pc-msdosdjgpp-gcc >/dev/null 2>&1");
#endif

    if (djgpp_check == 0 || djgpp_check2 == 0) {
        detectedBackend = CompilerBackend::DJGPP;
        std::cout << "[+] DJGPP compiler detected" << std::endl;
        return true;
    }

    // Try to detect Open Watcom
#ifdef _WIN32
    int watcom_check = system("where wcc386 >nul 2>&1");
#else
    int watcom_check = system("which wcc386 >/dev/null 2>&1");
#endif

    if (watcom_check == 0) {
        detectedBackend = CompilerBackend::OPEN_WATCOM;
        std::cout << "[+] Open Watcom compiler detected" << std::endl;
        return true;
    }

    std::cerr << "[-] No suitable DOS C compiler found. Please install DJGPP or Open Watcom." << std::endl;
    return false;
}

std::string CompilerPipeline::getCompilerCommand(CompilerBackend backend, const CompileOptions& opts) {
    std::ostringstream cmd;

    if (backend == CompilerBackend::DJGPP) {
        cmd << "i586-pc-msdosdjgpp-gcc";
        
        // Add optimization flags
        if (opts.optimizationLevel == "O0") cmd << " -O0";
        else if (opts.optimizationLevel == "O1") cmd << " -O1";
        else if (opts.optimizationLevel == "O2") cmd << " -O2";
        else if (opts.optimizationLevel == "O3") cmd << " -O3";
        else if (opts.optimizationLevel == "Os") cmd << " -Os";
        
        if (opts.generateDebugInfo) cmd << " -g";
        
        // Memory model for DOS
        if (opts.memoryModel == "large") cmd << " -mcmodel=large";
        else if (opts.memoryModel == "huge") cmd << " -mcmodel=huge";
        
        // Protected mode
        if (opts.memoryModel == "large" || opts.memoryModel == "huge") {
            cmd << " -D__PROTECTED_MODE__";
        }
    } else if (backend == CompilerBackend::OPEN_WATCOM) {
        cmd << "wcc386";
        if (opts.optimizationLevel == "O2") cmd << " -O2";
        if (opts.memoryModel == "large") cmd << " -ml";
    }

    return cmd.str();
}

CompileResult CompilerPipeline::compile(const std::vector<std::string>& sourceFiles, const CompileOptions& options) {
    CompileResult result = {false, "", "", "", 0, 0};
    
    if (detectedBackend == CompilerBackend::AUTO_DETECT) {
        result.errorLog = "Compiler not initialized. Call initialize() first.";
        return result;
    }

    std::string compilerCmd = getCompilerCommand(detectedBackend, options);
    std::ostringstream fullCmd;
    
    fullCmd << compilerCmd;
    
    // Add source files
    for (const auto& srcFile : sourceFiles) {
        fullCmd << " \"" << srcFile << "\"";
    }
    
    // Add output file
    fullCmd << " -o \"" << options.outputFile << "\"";
    
    std::cout << "[*] Compiling with: " << fullCmd.str() << std::endl;
    
    int compileStatus = system(fullCmd.str().c_str());
    
    if (compileStatus == 0) {
        result.success = true;
        result.executablePath = options.outputFile;
        result.compilationTime = 1; // Placeholder
        std::cout << "[+] Compilation successful!" << std::endl;
    } else {
        result.errorLog = "Compilation failed with exit code: " + std::to_string(compileStatus);
        std::cerr << "[-] " << result.errorLog << std::endl;
    }

    return result;
}

CompileResult CompilerPipeline::compileFile(const std::string& sourceFile, const CompileOptions& options) {
    return compile({sourceFile}, options);
}

std::string CompilerPipeline::getDOSLinkerScript(MemoryModel model) {
    std::string script = "; Wolfenstein 3D DOS Linker Script\n";
    
    if (model == MemoryModel::PROTECTED_MODE) {
        script += "STACKSIZE = 32768\n";
        script += "HEAP = 524288\n";
        script += "OUTPUT FORMAT elf32-i386\n";
    } else {
        script += "STACKSIZE = 4096\n";
        script += "HEAP = 65536\n";
        script += "OUTPUT FORMAT coff-i386\n";
    }
    
    return script;
}
