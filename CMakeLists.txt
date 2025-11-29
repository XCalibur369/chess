cmake_minimum_required(VERSION 3.16)
project(ChessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Specify the compiler explicitly
set(CMAKE_C_COMPILER "C:/Qt/Tools/mingw1310_64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Qt/Tools/mingw1310_64/bin/g++.exe")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED CONFIG)

set(SOURCES
    src/main.cpp
    src/Chess.cpp
    src/ChessBoard.cpp
    src/MainWindow.cpp
)

set(HEADERS
    include/Chess.h
    include/ChessBoard.h
    include/MainWindow.h
)

add_executable(ChessGame ${SOURCES} ${HEADERS})

target_include_directories(ChessGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ChessGame Qt6::Core Qt6::Gui Qt6::Widgets)
