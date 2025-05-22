cmake_minimum_required(VERSION 3.20)

# auto-detect platform and setting compiler
if(WIN32)
    # choose MSVC on Windows
    if(NOT CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Windows detected, setting compiler to MSVC")
        set(CMAKE_C_COMPILER "cl")
        set(CMAKE_GENERATOR_PLATFORM "x64")
    endif()
elseif(UNIX AND NOT APPLE)
    # choose GCC on Linux
    if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Linux detected, setting compiler to GCC")
        find_program(GCC_COMPILER gcc)
        if(GCC_COMPILER)
            set(CMAKE_C_COMPILER "${GCC_COMPILER}")
        else()
            message(WARNING "GCC not found, using default compiler")
        endif()
    endif()
elseif(APPLE)
    # choose clang on macOS
    message(STATUS "macOS detected, using system Clang")
endif()

project(RTD26xx_I2C_Programer
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Od /Zi")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2")
    endif()
endif()

# source files
set(SOURCES
    main.c
    crc.c
    gff.c
    i2c.c
)

#  header files
set(HEADERS
    crc.h
    gff.h
    i2c.h
    nor.h
)

# create execute file
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# add include folder
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# specific platform
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(STATUS "Building for x64 (AMD64) architecture")
    else()
        message(WARNING "Not building for x64 architecture!")
    endif()

    if(MSVC)
        set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
        set_property(TARGET ${PROJECT_NAME} PROPERTY VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE "x64")
    endif()
elseif(UNIX AND NOT APPLE)
    # target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VS_STARTUP_PROJECT ${PROJECT_NAME}
    )
endif()

message(STATUS "=== Build Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} (${CMAKE_C_COMPILER})")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Architecture: ${CMAKE_SYSTEM_PROCESSOR}")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Target Architecture: x64 (64-bit)")
else()
    message(STATUS "Target Architecture: x86 (32-bit)")
endif()
message(STATUS "=============================")
