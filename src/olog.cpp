#include "../include/olog.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace OLog {
static std::ofstream log_file;
static int flags;
static int exit_code = 50;

void setOLogExitCode(const int code) { exit_code = code; }

void openLogFile(const std::string& file_name, const int _flags) {
    if (!log_file.is_open()) {
        log_file.open(file_name, std::ios::app);

        if (!log_file.is_open()) {
            throw std::ios_base::failure("Could not open log file");
        }
        log_file << "====NEW SESSION STARTED====" << std::endl;
        log_file.flush();
        flags = _flags;
    } else {
        throw std::logic_error("Log file already open");
    }
}

void closeLogFile() { log_file.close(); }

void log(const LogLevel level, const std::string& message, const int time) {
    if (!log_file.is_open()) {
        throw std::runtime_error("Log file not open");
    }

    std::string level_text;
    switch (level) {
    case LogLevel::DEBUG:
        level_text = "DEBUG";
        break;
    case LogLevel::INFO:
        level_text = "INFO";
        break;
    case LogLevel::WARNING:
        level_text = "WARNING";
        break;
    case LogLevel::ERROR:
        level_text = "ERROR";
        break;
    case LogLevel::CRITICAL:
        level_text = "CRITICAL ERROR";
        break;
    }

    std::ostringstream log_entry;

    if (time == -1)
        log_entry << level_text << " - " << message << std::endl;
    else
        log_entry << "[" << time << "] " << level_text << " - " << message << std::endl;

    log_file << log_entry.str();
    log_file.flush();

    if (flags & OL_LOG_TO_STDOUT) {
        std::cout << log_entry.str();
    }

    if (flags & OL_QUIT_ON_CRITICAL) {
        closeLogFile();
        exit(exit_code);
    }
}

} // namespace OLog
