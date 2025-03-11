#include <gtest/gtest.h>
#include <fstream>
#include "../include/olog.h"

TEST(OLogTest, TestBasicLogging) {
    OLog::openLogFile("test.log");
    OLog::log(OLog::LogLevel::DEBUG, "Hello world!");
    OLog::log(OLog::LogLevel::INFO, "Hello world!");
    OLog::log(OLog::LogLevel::WARNING, "Hello world!");
    OLog::log(OLog::LogLevel::ERROR, "Hello world!");
    OLog::log(OLog::LogLevel::CRITICAL, "Hello world!");
    OLog::closeLogFile();

    std::ifstream log_file("test.log");
    ASSERT_TRUE(log_file.is_open());

    std::string line;
    std::stringstream log_content;
    while (std::getline(log_file, line)) {
        log_content << line << "\n";
    }

    std::string content = log_content.str();

    EXPECT_NE(content.find("DEBUG - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("INFO - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("WARNING - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("ERROR - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("CRITICAL ERROR - Hello world!"), std::string::npos);

    std::remove("test.log");
}

TEST(OLogTest, TestBasicLoggingWithTime) {
    OLog::openLogFile("test.log");
    OLog::log(OLog::LogLevel::DEBUG, "Hello world!", 1);
    OLog::log(OLog::LogLevel::INFO, "Hello world!", 20);
    OLog::log(OLog::LogLevel::WARNING, "Hello world!", 100);
    OLog::log(OLog::LogLevel::ERROR, "Hello world!", 2000);
    OLog::log(OLog::LogLevel::CRITICAL, "Hello world!", 10000);
    OLog::closeLogFile();

    std::ifstream log_file("test.log");
    ASSERT_TRUE(log_file.is_open());

    std::string line;
    std::stringstream log_content;
    while (std::getline(log_file, line)) {
        log_content << line << "\n";
    }

    std::string content = log_content.str();

    EXPECT_NE(content.find("[1] DEBUG - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("[20] INFO - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("[100] WARNING - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("[2000] ERROR - Hello world!"), std::string::npos);
    EXPECT_NE(content.find("[10000] CRITICAL ERROR - Hello world!"), std::string::npos);

    std::remove("test.log");
}

TEST(OLogTest, TestRepeatedLogging) {
    OLog::openLogFile("test.log");
    OLog::log(OLog::LogLevel::DEBUG, "Hello world!");
    OLog::closeLogFile();

    OLog::openLogFile("test.log");
    OLog::log(OLog::LogLevel::DEBUG, "Hello world again!");
    OLog::closeLogFile();

    std::ifstream log_file("test.log");
    ASSERT_TRUE(log_file.is_open());

    std::string line;
    std::getline(log_file, line);
    EXPECT_EQ(line, "====NEW SESSION STARTED====");
    std::getline(log_file, line);
    EXPECT_EQ(line, "DEBUG - Hello world!");

    std::remove("test.log");
}

TEST(OLogTest, TestLogToStdout) {
    std::ostringstream log_stream;
    OLog::openLogFile("test.log", OLog::OL_LOG_TO_STDOUT);

    // Redirect std::cout to log_stream to capture stdout output
    std::streambuf* original_stream = std::cout.rdbuf();
    std::cout.rdbuf(log_stream.rdbuf());

    OLog::log(OLog::LogLevel::INFO, "This is a test log message");

    EXPECT_TRUE(log_stream.str().find("INFO - This is a test log message") != std::string::npos);

    // Restore the original stream
    std::cout.rdbuf(original_stream);

    OLog::closeLogFile();

    std::ifstream log_file("test.log");
    ASSERT_TRUE(log_file.is_open());
    std::string line;
    std::stringstream log_content;
    while (std::getline(log_file, line)) {
        log_content << line << "\n";
    }
    std::string content = log_content.str();
    EXPECT_NE(content.find("INFO - This is a test log message"), std::string::npos);
    std::remove("test.log");
}

TEST(OLogTest, OpenLogFileThrowsWhenAlreadyOpen) {
    OLog::openLogFile("test.log");
    EXPECT_THROW(OLog::openLogFile("test.log"), std::logic_error);
    OLog::closeLogFile();
    std::remove("test.log");
}

TEST(OLogTest, LogThrowsIfFileNotOpen) {
    EXPECT_THROW(OLog::log(OLog::LogLevel::INFO, "This is a test log message"), std::runtime_error);
}

TEST(OLogTest, LogExitsOnCriticalError) {
    OLog::openLogFile("test.log", OLog::OL_QUIT_ON_CRITICAL);
    EXPECT_EXIT(OLog::log(OLog::LogLevel::CRITICAL, "Critical error encountered"), ::testing::ExitedWithCode(50), "");

    OLog::closeLogFile();
    std::remove("test.log");
}

TEST(OLogTest, SetOLogExitCodeChangesExitCode) {
    OLog::openLogFile("test.log", OLog::OL_QUIT_ON_CRITICAL);
    OLog::setOLogExitCode(22);
    EXPECT_EXIT(OLog::log(OLog::LogLevel::CRITICAL, "Critical error encountered"), ::testing::ExitedWithCode(22), "");

    OLog::closeLogFile();
    std::remove("test.log");
}
