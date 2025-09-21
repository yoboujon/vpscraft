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

if(WIN32)
    set(RESOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/resources.rc")
else()
    set(RESOURCE_FILE "")
endif()

# Dependencies
find_package(libssh CONFIG REQUIRED)

# Shared library
set(TARGET "${APP_NAME_LOW}_lib")
set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")
add_library(
	${TARGET} SHARED
    ${SOURCES}/error.cpp
	${SOURCES}/ssh.cpp
    ${SOURCES}/vpscraft.cpp
)
target_include_directories(
	${TARGET} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(
    ${TARGET} PUBLIC
    ssh
)
set_target_properties(${TARGET} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${APP_NAME_LOW})

# CLI Executable
set(TARGET "${APP_NAME_LOW}_cli")
set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/cli")
add_executable(
	${TARGET}
	${SOURCES}/main.cpp
)
target_link_libraries(
    ${TARGET} PRIVATE
    "${APP_NAME_LOW}_lib"
    ssh
)

# UI Executable
include(cmake/qt.cmake)

# Installer
include(cmake/cpack.cmake)
