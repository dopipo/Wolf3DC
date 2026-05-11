#include "logger.h"
#include <iostream>
#include <cstdarg>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() 
    : minLogLevel(LogLevel::DEBUG), 
      consoleOutput(true), 
      fileOutput(false) {}

Logger::~Logger() {
    close();
}

bool Logger::initialize(const std::string& logFilePath) {
    this->logFilePath = logFilePath;
    logFile = std::make_unique<std::ofstream>(logFilePath, std::ios::app);
    
    if (!logFile || !logFile->is_open()) {
        std::cerr << "ERROR: Cannot open log file: " << logFilePath << std::endl;
        return false;
    }
    
    fileOutput = true;
    return true;
}

std::string Logger::getTimestamp() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::getLevelString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::ERROR:    return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default:                 return "UNKNOWN";
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < minLogLevel) {
        return;
    }
    
    std::string timestamp = getTimestamp();
    std::string levelStr = getLevelString(level);
    std::string logMessage = "[" + timestamp + "] [" + levelStr + "] " + message;
    
    // Вывод в консоль
    if (consoleOutput) {
        if (level >= LogLevel::ERROR) {
            std::cerr << logMessage << std::endl;
        } else {
            std::cout << logMessage << std::endl;
        }
    }
    
    // Вывод в файл
    if (fileOutput && logFile && logFile->is_open()) {
        *logFile << logMessage << std::endl;
        logFile->flush();
    }
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::critical(const std::string& message) {
    log(LogLevel::CRITICAL, message);
}

void Logger::logf(LogLevel level, const char* format, ...) {
    if (level < minLogLevel) {
        return;
    }
    
    char buffer[4096];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    log(level, std::string(buffer));
}

void Logger::errorf(const char* format, ...) {
    char buffer[4096];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    error(std::string(buffer));
}

void Logger::infof(const char* format, ...) {
    char buffer[4096];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    info(std::string(buffer));
}

void Logger::setMinLogLevel(LogLevel level) {
    minLogLevel = level;
}

void Logger::setConsoleOutput(bool enabled) {
    consoleOutput = enabled;
}

void Logger::setFileOutput(bool enabled) {
    fileOutput = enabled;
}

void Logger::close() {
    if (logFile && logFile->is_open()) {
        logFile->close();
    }
}