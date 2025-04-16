#include "log.hpp"

void Log::message(LogLevel level, const std::string& message) {
    logs.push_back({getCurrentTime(), level, message});
    if (logs.size() > MAX_LOG_ENTRIES) {
        logs.pop_front();
    }
}

void Log::print() {
    std::cout << "\nLast 10 events:\n";
    for (const auto& entry : logs) {
        std::cout << "[" << entry.time << "] ";
        switch (entry.level) {
            case LOG_NORMAL: std::cout << "NORMAL: "; break;
            case LOG_WARNING: std::cout << "WARNING: "; break;
            case LOG_ERROR: std::cout << "ERROR: "; break;
        }
        std::cout << entry.message << "\n";
    }
    std::cout << std::endl;
}