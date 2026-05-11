#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <ctime>
#include <iomanip>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

class Logger {
public:
    static Logger& getInstance();
    
    // Инициализация логгера с файлом
    bool initialize(const std::string& logFilePath);
    
    // Основные методы логирования
    void log(LogLevel level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);
    
    // Логирование с форматированием
    void logf(LogLevel level, const char* format, ...);
    void errorf(const char* format, ...);
    void infof(const char* format, ...);
    
    // Установка минимального уровня логирования
    void setMinLogLevel(LogLevel level);
    
    // Переключение вывода в консоль/файл
    void setConsoleOutput(bool enabled);
    void setFileOutput(bool enabled);
    
    // Закрытие логгера
    void close();
    
    ~Logger();

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    std::unique_ptr<std::ofstream> logFile;
    LogLevel minLogLevel;
    bool consoleOutput;
    bool fileOutput;
    std::string logFilePath;
    
    std::string getTimestamp() const;
    std::string getLevelString(LogLevel level) const;
};

#endif // LOGGER_H
