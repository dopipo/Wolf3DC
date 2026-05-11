#ifndef IDE_INTERFACE_H
#define IDE_INTERFACE_H

#include "project_manager.h"
#include "compiler_pipeline.h"
#include <string>
#include <vector>

class IDEInterface {
private:
    ProjectManager projectManager;
    CompilerPipeline compiler;
    bool running;

    // UI Helper functions
    void printMenu();
    void printProjectMenu();
    void printCompileMenu();
    void clearScreen();
    void printHeader();
    void printFooter();
    
    // Command handlers
    void handleNewProject();
    void handleOpenProject();
    void handleAddFile();
    void handleCompile();
    void handleRun();
    void handleProjectSettings();

public:
    IDEInterface();
    ~IDEInterface();

    bool initialize();
    void run();
    void shutdown();
};

#endif // IDE_INTERFACE_H
