#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>

namespace Animation {
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
}

#endif // ANIMATION_H
