cmake_minimum_required(VERSION 3.5)

project(hangman)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

add_compile_options(-std=c++11 -O3)

file(GLOB_RECURSE SRCS src/*.cpp)
add_executable(hangman ${SRCS})

target_link_libraries(hangman Qt5::Core)
target_link_libraries(hangman Qt5::Widgets)
target_link_libraries(hangman Qt5::Gui)

file(COPY "data" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "VERSION" DESTINATION "${CMAKE_BINARY_DIR}/data")

install(TARGETS hangman DESTINATION bin)
install(DIRECTORY "data" DESTINATION "share/hangman")
install(FILES "VERSION" DESTINATION "share/hangman/data")
install(FILES "hangman.desktop" DESTINATION "share/applications")
install(FILES "hangman.svg" DESTINATION "share/pixmaps")

include(InstallRequiredSystemLibraries)

file(STRINGS "VERSION" VERSION_STRING)

set(CPACK_PACKAGE_VERSION "${VERSION_STRING}")
set(CPACK_PACKAGE_NAME "hangman")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A game of hangman with multiple word categories, supporting multiple languages.")
set(CPACK_PACKAGE_DESCRIPTION "A game of hangman with multiple word categories, supporting multiple languages.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES "build/hangman")
set(CPACK_PACKAGE_EXECUTABLES "hangman" "Hangman")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Rob Jinman <admin@robjinman.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qtdeclarative5-dev (>= 5.5.1)")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
set(CPACK_DEBIAN_PACKAGE_SECTION games)

message("${CPACK_DEBIAN_PACKAGE_VERSION}")
set(CPACK_GENERATOR "DEB")
include(CPack)

