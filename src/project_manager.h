#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <string>
#include <vector>
#include <map>

struct CompilerSettings {
    std::string optimizationLevel;  // O0, O1, O2, O3, Os
    bool debugInfo;
    std::string targetPlatform;     // dos_real, dos_protected, native
    std::vector<std::string> defines;
    std::vector<std::string> includePaths;
    std::string memoryModel;        // compact, large, huge
};

struct W3DProject {
    std::string projectName;
    std::string projectPath;
    std::vector<std::string> cSourceFiles;
    std::vector<std::string> asmSourceFiles;
    std::string mainSourceFile;
    std::string outputFile;
    CompilerSettings settings;
};

class ProjectManager {
private:
    W3DProject currentProject;
    bool projectLoaded;

public:
    ProjectManager();
    ~ProjectManager();

    // Project lifecycle
    bool createNewProject(const std::string& name, const std::string& path);
    bool loadProject(const std::string& prjFilePath);
    bool saveProject();

    // File management
    bool addSourceFile(const std::string& filePath);
    bool removeSourceFile(const std::string& filePath);
    std::vector<std::string> getSourceFiles() const;

    // Project properties
    std::string getProjectName() const { return currentProject.projectName; }
    std::string getProjectPath() const { return currentProject.projectPath; }
    std::string getOutputFile() const { return currentProject.outputFile; }
    CompilerSettings& getSettings() { return currentProject.settings; }

    // Borland .PRJ format parsing
    bool parseBorlandPRJ(const std::string& filePath);
    bool writeBorlandPRJ(const std::string& filePath);
};

#endif // PROJECT_MANAGER_H
