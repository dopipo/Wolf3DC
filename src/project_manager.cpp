#include "project_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

ProjectManager::ProjectManager() : projectLoaded(false) {}

ProjectManager::~ProjectManager() {}

bool ProjectManager::createNewProject(const std::string& name, const std::string& path) {
    currentProject.projectName = name;
    currentProject.projectPath = path;
    currentProject.outputFile = name + ".exe";
    
    // Default compiler settings for W3D (DOS protected mode)
    currentProject.settings.targetPlatform = "dos_protected";
    currentProject.settings.optimizationLevel = "O2";
    currentProject.settings.memoryModel = "large";
    currentProject.settings.debugInfo = true;
    
    projectLoaded = true;
    return true;
}

bool ProjectManager::loadProject(const std::string& prjFilePath) {
    if (!parseBorlandPRJ(prjFilePath)) {
        return false;
    }
    projectLoaded = true;
    return true;
}

bool ProjectManager::saveProject() {
    if (!projectLoaded) return false;
    std::string prjPath = currentProject.projectPath + "/" + currentProject.projectName + ".PRJ";
    return writeBorlandPRJ(prjPath);
}

bool ProjectManager::addSourceFile(const std::string& filePath) {
    if (filePath.find(".c") != std::string::npos || filePath.find(".C") != std::string::npos) {
        currentProject.cSourceFiles.push_back(filePath);
        return true;
    } else if (filePath.find(".asm") != std::string::npos || filePath.find(".ASM") != std::string::npos) {
        currentProject.asmSourceFiles.push_back(filePath);
        return true;
    }
    return false;
}

bool ProjectManager::removeSourceFile(const std::string& filePath) {
    auto& cFiles = currentProject.cSourceFiles;
    auto it = std::find(cFiles.begin(), cFiles.end(), filePath);
    if (it != cFiles.end()) {
        cFiles.erase(it);
        return true;
    }
    
    auto& asmFiles = currentProject.asmSourceFiles;
    auto asm_it = std::find(asmFiles.begin(), asmFiles.end(), filePath);
    if (asm_it != asmFiles.end()) {
        asmFiles.erase(asm_it);
        return true;
    }
    return false;
}

std::vector<std::string> ProjectManager::getSourceFiles() const {
    std::vector<std::string> allFiles = currentProject.cSourceFiles;
    allFiles.insert(allFiles.end(), currentProject.asmSourceFiles.begin(), currentProject.asmSourceFiles.end());
    return allFiles;
}

bool ProjectManager::parseBorlandPRJ(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Cannot open project file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    std::string section;
    
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == ';') continue;
        
        // Parse sections [PRJ], [FILES], [OPTIONS]
        if (line[0] == '[' && line[line.length() - 1] == ']') {
            section = line.substr(1, line.length() - 2);
            continue;
        }

        // Parse project name
        if (section == "PRJ" && line.find("ProjectName=") != std::string::npos) {
            currentProject.projectName = line.substr(line.find('=') + 1);
        }
        
        // Parse files
        if (section == "FILES" && !line.empty()) {
            if (line.find(".c") != std::string::npos || line.find(".C") != std::string::npos) {
                currentProject.cSourceFiles.push_back(line);
            } else if (line.find(".asm") != std::string::npos || line.find(".ASM") != std::string::npos) {
                currentProject.asmSourceFiles.push_back(line);
            }
        }
        
        // Parse options
        if (section == "OPTIONS") {
            if (line.find("Optimization=") != std::string::npos) {
                currentProject.settings.optimizationLevel = line.substr(line.find('=') + 1);
            }
            if (line.find("MemoryModel=") != std::string::npos) {
                currentProject.settings.memoryModel = line.substr(line.find('=') + 1);
            }
            if (line.find("DebugInfo=") != std::string::npos) {
                currentProject.settings.debugInfo = (line.find("true") != std::string::npos);
            }
        }
    }

    file.close();
    return true;
}

bool ProjectManager::writeBorlandPRJ(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Cannot write project file: " << filePath << std::endl;
        return false;
    }

    file << ";" << std::endl;
    file << "; Wolfenstein 3D Borland C Project" << std::endl;
    file << ";" << std::endl << std::endl;

    file << "[PRJ]" << std::endl;
    file << "ProjectName=" << currentProject.projectName << std::endl;
    file << "Output=" << currentProject.outputFile << std::endl << std::endl;

    file << "[FILES]" << std::endl;
    for (const auto& cFile : currentProject.cSourceFiles) {
        file << cFile << std::endl;
    }
    for (const auto& asmFile : currentProject.asmSourceFiles) {
        file << asmFile << std::endl;
    }
    file << std::endl;

    file << "[OPTIONS]" << std::endl;
    file << "Optimization=" << currentProject.settings.optimizationLevel << std::endl;
    file << "MemoryModel=" << currentProject.settings.memoryModel << std::endl;
    file << "DebugInfo=" << (currentProject.settings.debugInfo ? "true" : "false") << std::endl;
    file << "Platform=" << currentProject.settings.targetPlatform << std::endl;

    file.close();
    return true;
}
