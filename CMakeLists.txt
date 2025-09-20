cmake_minimum_required(VERSION 3.15)
project(
    VPSCraft 
    VERSION 0.1.0
    DESCRIPTION "Open Source VPS Minecraft Server Manager"
    HOMEPAGE_URL "https://www.etheryo.fr/"
    LANGUAGES CXX C
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(APP_NAME "VPSCraft")
string(TOLOWER "${APP_NAME}" APP_NAME_LOW)
set(QT_SUBDIR "ui")

# Shared library
set(TARGET "${APP_NAME_LOW}_lib")
set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_library(
	${TARGET} SHARED
	${SOURCES}/lib.cpp
)
target_include_directories(
	${TARGET} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set_target_properties(${TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${APP_NAME_LOW})

# Executable
include(cmake/qt.cmake)

# Installer
include(cmake/cpack.cmake)
