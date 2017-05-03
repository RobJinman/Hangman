cmake_minimum_required(VERSION 3.5)

project(hangman)
add_subdirectory(tools)

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

install(TARGETS hangman DESTINATION "bin")
install(DIRECTORY "data" DESTINATION "share/hangman")
install(FILES "hangman.sh" DESTINATION "games" RENAME "hangman")
install(FILES "VERSION" DESTINATION "share/hangman/data")
install(FILES "hangman.desktop" DESTINATION "share/applications")
install(FILES "hangman.svg" DESTINATION "share/pixmaps")

include(InstallRequiredSystemLibraries)
