#ifndef LOG_H
#define LOG_H

#include <string>
#include <deque>
#include <chrono>
#include <ctime>
#include <iostream>

enum LogLevel {
    LOG_NORMAL,
    LOG_WARNING,
    LOG_ERROR
};

class Log {
public:
    static Log* Instance() {
        static Log instance;
        return &instance;
    }

    void message(LogLevel level, const std::string& message);
    void print();

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    Log() = default;
    ~Log() = default;

    struct LogEntry {
        std::string time;
        LogLevel level;
        std::string message;
    };

    std::deque<LogEntry> logs;
    static const int MAX_LOG_ENTRIES = 10;

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm;

        #ifdef _WIN32
        localtime_s(&tm, &time);
        #else
        localtime_r(&time, &tm);
        #endif

        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        return buffer;
    }
};

#endif // LOG_H