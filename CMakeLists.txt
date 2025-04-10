cmake_minimum_required(VERSION 3.25)
project(OLog VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT TARGET OLog)
    add_library(OLog STATIC src/olog.cpp)

    target_include_directories(OLog PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    install(TARGETS OLog
            EXPORT OLogTargets
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
    )

    install(DIRECTORY include/ DESTINATION include)

    install(EXPORT OLogTargets
            FILE OLogTargets.cmake
            NAMESPACE OLog::
            DESTINATION lib/cmake/OLog
    )
endif()


if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    enable_testing()
    add_subdirectory(tests)
endif()