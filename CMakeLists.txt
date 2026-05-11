cmake_minimum_required(VERSION 3.10)
project(W3D_Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(w3d_compiler
    src/main.cpp
    src/compiler.cpp
    src/lexer.cpp
    src/parser.cpp
    src/logger.cpp
    src/dos_support.cpp
    src/android_support.cpp
)

# Включаемые директории
target_include_directories(w3d_compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Флаги компиляции
if(MSVC)
    target_compile_options(w3d_compiler PRIVATE /W4)
else()
    target_compile_options(w3d_compiler PRIVATE -Wall -Wextra -Wpedantic)
endif()

# DOS специфичные флаги
if(CMAKE_SYSTEM_NAME STREQUAL "DJGPP")
    target_compile_options(w3d_compiler PRIVATE -m32)
    target_link_options(w3d_compiler PRIVATE -m32)
endif()

# Android специфичные флаги
if(ANDROID)
    target_compile_definitions(w3d_compiler PRIVATE ANDROID_BUILD)
    target_compile_definitions(w3d_compiler PRIVATE USE_OPENGL_ES)
endif()

# Мобильные платформы - отключаем файловое логирование если нужно
if(ANDROID OR IOS)
    target_compile_definitions(w3d_compiler PRIVATE MOBILE_PLATFORM)
endif()

# Linux/Unix поддержка
if(UNIX AND NOT APPLE AND NOT ANDROID)
    target_compile_definitions(w3d_compiler PRIVATE LINUX_BUILD)
endif()

# macOS поддержка
if(APPLE)
    target_compile_definitions(w3d_compiler PRIVATE MACOS_BUILD)
endif()
