#pragma once

#include <string>

/// @def OL_LOG_TO_STDOUT
/// @brief Flag to enable logging to standard output.
#define OL_LOG_TO_STDOUT 1<<0

/// @def OL_QUIT_ON_CRITICAL
/// @brief Flag to terminate the program on a critical log message.
#define OL_QUIT_ON_CRITICAL 1<<1

/// @namespace OLog
/// @brief A simple logging library for writing logs to a file and optionally to stdout.
namespace OLog {
    /// @enum LogLevel
    /// @brief Defines various log severity levels.
    enum LogLevel {
        DEBUG,    ///< Debug-level messages for troubleshooting.
        INFO,     ///< Informational messages.
        WARNING,  ///< Warning messages that indicate potential issues.
        ERROR,    ///< Error messages indicating failures.
        CRITICAL  ///< Critical messages that may cause program termination.
    };

    /**
     * @brief Opens a log file for writing.
     *
     * This function attempts to open the specified log file. If successful, it appends
     * log messages to the file. If the file is already open, an exception is thrown.
     * A new session header is written at the beginning.
     *
     * @param file_name The name of the log file.
     * @param _flags Flags controlling logging behavior (e.g., `OL_LOG_TO_STDOUT`).
     *
     * @throws std::logic_error If the log file is already open. The user must close the
     * existing log file before opening a new one.
     * @throws std::ios_base::failure If the log file cannot be opened due to file system
     * errors (e.g., missing permissions, invalid file path).
     */
    void openLogFile(const std::string &file_name, int _flags=0);

    /**
     * @brief Closes the currently opened log file.
     *
     * This function closes the log file if it is open. After calling this, logging
     * to the file will not be possible until `openLogFile()` is called again.
     */
    void closeLogFile();

    /**
     * @brief Logs a message with a given severity level.
     *
     * Logs messages to the file and optionally to `stdout`, based on the flags set.
     * If logging a `CRITICAL` error and the `OL_QUIT_ON_CRITICAL` flag is set, the
     * program will terminate with the specified exit code.
     *
     * @param level The severity level of the log message.
     * @param message The message to be logged.
     * @param time (Optional) A timestamp for the log entry. If `-1`, the time is not logged.
     *
     * @throws std::runtime_error If the log file is not open.
     */
    void log(LogLevel level, const std::string &message, int time=-1);

    /**
     * @brief Sets the exit code used when a critical log message forces program termination.
     *
     * This function allows setting a custom exit code when `OL_QUIT_ON_CRITICAL` is enabled.
     *
     * @param code The exit code to use when terminating due to a critical error.
     */
    void setOLogExitCode(int code);

} // namespace OLog