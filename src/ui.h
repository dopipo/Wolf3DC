#ifndef UI_H
#define UI_H

#include <string>
#include <iostream>
#include <vector>

class UI {
public:
    enum class Color {
        BLACK = 0,
        RED = 1,
        GREEN = 2,
        YELLOW = 3,
        BLUE = 4,
        MAGENTA = 5,
        CYAN = 6,
        WHITE = 7
    };

    // Вывод заголовка
    static void printHeader();
    
    // Вывод футера
    static void printFooter();
    
    // Вывод разделителя
    static void printSeparator(char c = '=', int width = 60);
    static void printDottedSeparator(int width = 60);
    
    // Цветной вывод
    static void printColored(const std::string& text, Color color);
    static void printSuccess(const std::string& text);
    static void printError(const std::string& text);
    static void printWarning(const std::string& text);
    static void printInfo(const std::string& text);
    static void printDebug(const std::string& text);
    
    // Вывод шагов
    static void printStep(int step, const std::string& description);
    static void printSubStep(const std::string& description);
    
    // Вывод статистики
    static void printStats(const std::string& label, const std::string& value);
    static void printStatsHeader();
    static void printStatsFooter();
    
    // Прогресс
    static void printProgress(int current, int total, const std::string& task);
    
    // Таблица результатов
    static void printTableHeader(const std::vector<std::string>& columns);
    static void printTableRow(const std::vector<std::string>& values);
    static void printTableSeparator(const std::vector<int>& widths);
    
    // Центрирование текста
    static std::string centerText(const std::string& text, int width = 60);
    
    // Очистка экрана
    static void clearScreen();
    
    // Использование цветов (Windows/Unix)
    static bool supportsColor();
    
private:
    static std::string getColorCode(Color color, bool background = false);
    static std::string resetColor();
};

#endif // UI_H
