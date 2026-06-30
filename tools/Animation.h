#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
#define byte win_byte
#include <windows.h>
#undef byte
#endif

namespace Animation {
    // ANSI Color Codes
    inline const std::string BLUE = "\033[1;34m";
    inline const std::string CYAN = "\033[1;36m";
    inline const std::string RESET = "\033[0m";
    inline const std::string WHITE = "\033[1;37m";
    inline const std::string GRAY = "\033[90m";
    inline const std::string BOLD = "\033[1m";

    inline void initConsole() {
#ifdef _WIN32
        // Enable virtual terminal processing for ANSI color codes on Windows console
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
#endif
    }

    // High-resolution busy-wait sleep for sub-millisecond precision
    inline void preciseSleepUs(long long microseconds) {
        auto start = std::chrono::high_resolution_clock::now();
        while (std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now() - start)
                   .count() < microseconds) {
            // Busy wait to bypass Windows standard sleep scheduler resolution limit (~15ms)
        }
    }

    // Calculates appropriate delays based on the total number of rows in the table
    inline void getDelaysForCount(int rowCount, int& charDelayUs, int& lineDelayMs, int& postLineDelayMs) {
        if (rowCount <= 0) {
            charDelayUs = 200;
            lineDelayMs = 8;
            postLineDelayMs = 4;
            return;
        }
        
        // Target around 250ms total table rendering time
        int totalTargetMs = 250;
        int perRowTargetMs = totalTargetMs / rowCount;
        
        // Clamp per row rendering target between 5ms and 35ms
        perRowTargetMs = std::max(5, std::min(35, perRowTargetMs));
        
        // Assume an average table row length of 80 characters
        charDelayUs = (perRowTargetMs * 1000) / 80;
        
        // Dynamic line delays for borders/headers
        lineDelayMs = std::max(2, std::min(25, perRowTargetMs));
        postLineDelayMs = std::max(1, std::min(15, perRowTargetMs / 2));
    }

    // Character-by-character typewriter effect with microsecond precision
    inline void typeWrite(const std::string& text, int charDelayUs) {
        for (char c : text) {
            std::cout << c << std::flush;
            if (charDelayUs > 0) {
                preciseSleepUs(charDelayUs);
            }
        }
    }

    // Prints a full line instantly but sleeps briefly after the line
    inline void printLineDelayed(const std::string& line, int lineDelayMs) {
        std::cout << line << std::endl;
        if (lineDelayMs > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(lineDelayMs));
        }
    }

    // Prints a line using the microsecond character typewriter, then pauses briefly
    inline void typeWriteLine(const std::string& line, int charDelayUs, int postLineDelayMs) {
        typeWrite(line, charDelayUs);
        std::cout << std::endl;
        if (postLineDelayMs > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(postLineDelayMs));
        }
    }

    // Beautiful loading animation in blue/cyan that takes exactly 2 seconds
    inline void showLoading(const std::string& message) {
        const int total_duration_ms = 2000;
        const int step_ms = 100;
        const int steps = total_duration_ms / step_ms;
        
        std::cout << std::endl;
        char spinner[] = {'|', '/', '-', '\\'};
        for (int i = 0; i <= steps; ++i) {
            // Carriage return and clear screen command is not strictly needed if we overwrite,
            // but let's carriage return and write the message.
            std::cout << "\r" << BLUE << message << " " << CYAN << "[" << spinner[i % 4] << "] [";
            
            int barWidth = 20;
            int pos = (i * barWidth) / steps;
            for (int j = 0; j < barWidth; ++j) {
                if (j < pos) std::cout << "=";
                else if (j == pos) std::cout << ">";
                else std::cout << " ";
            }
            int percent = (i * 100) / steps;
            std::cout << "] " << percent << "%" << RESET << std::flush;
            
            if (i < steps) {
                std::this_thread::sleep_for(std::chrono::milliseconds(step_ms));
            }
        }
        std::cout << CYAN << " Done!" << RESET << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

#endif // ANIMATION_H
