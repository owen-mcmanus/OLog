
# OLog - A Simple Logging Library

OLog is a simple logging library designed to write logs to a file and optionally to stdout. It supports different log levels and flags that allow the user to customize the logging behavior, including terminating the program on critical errors.

## Features

- **Log to File**: Logs messages to a specified file.
- **Log Levels**: Supports multiple log levels: DEBUG, INFO, WARNING, ERROR, and CRITICAL.
- **Log to Console**: Optionally logs to standard output (stdout) based on flags.
- **Critical Error Handling**: Optionally terminates the program when a critical error is logged.
- **Timestamping**: Optionally logs the timestamp with each message.

## Documentation
Full documentation can be found here: https://owen-mcmanus.github.io/OLog/namespaceOLog.html

## Installation
Olog can be installed with cmake.  
To compile on Unix based systems run:
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `make install`

## Usage

To use this library in your project, include the `olog.h` header file and link against the library.
To link against the library with `g++` use the `-lOLog` flag.

1. **Include the Header**:


   ```cpp
   #include <olog.h>
   ```

2. **Opening a Log File**:

   Before logging any messages, open a log file by calling `openLogFile`:

   ```cpp
   OLog::openLogFile("my_log.txt", OLog::OL_LOG_TO_STDOUT);
   ```

    - `OLog::OL_LOG_TO_STDOUT`: Optionally enables logging to standard output.

3. **Logging Messages**:

   You can log messages with different severity levels:

   ```cpp
   OLog::log(OLog::LogLevel::INFO, "This is an informational message.");
   OLog::log(OLog::LogLevel::ERROR, "This is an error message.");
   ```

4. **Close the Log File**:

   After you're done logging, close the log file:

   ```cpp
   OLog::closeLogFile();
   ```

5. **Critical Error Handling**:

   If `OLog::OL_QUIT_ON_CRITICAL` is enabled, the program will terminate if a critical error is logged:

   ```cpp
   OLog::log(OLog::LogLevel::CRITICAL, "Critical error occurred!");
   ```

   Optionally, you can set a custom exit code for critical errors:

   ```cpp
   OLog::setOLogExitCode(100);
   ```

### Example

```cpp
#include <iostream>
#include <exception>
#include <olog.h>

int main() {
    try {
        // Open log file with options to log to stdout
        OLog::openLogFile("app_log.txt", OLog::OL_LOG_TO_STDOUT);

        // Log various messages
        OLog::log(OLog::LogLevel::INFO, "Application started.");
        OLog::log(OLog::LogLevel::DEBUG, "Debugging the process...");
        OLog::log(OLog::LogLevel::ERROR, "An error occurred!");
        
        // Log a critical message (program will exit with exit code 50)
        OLog::log(OLog::LogLevel::CRITICAL, "Critical error - exiting.");

        // Close the log file
        OLog::closeLogFile();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
```

## Contributing

Contributions are welcome! To contribute to this project, fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
