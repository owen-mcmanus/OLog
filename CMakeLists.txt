cmake_minimum_required(VERSION 3.25)
project(OLog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/olog.cpp
)

add_library(OLog STATIC ${SOURCES})

install(TARGETS OLog DESTINATION /usr/local/lib)
install(DIRECTORY include/ DESTINATION /usr/local/include)

enable_testing()
add_subdirectory(tests)