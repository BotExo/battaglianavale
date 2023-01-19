#De Maria Giovanni
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Battaglia_navale LANGUAGES CXX)

set(CMAKE_CXX_FLAGS"-O2")

add_executable(battaglia_navale
    battaglia_navale.cpp
)

add_executable(replay
    replay.cpp
)


add_library(Ships
    Ship.h
    Ship.cpp
)

add_library(Tabelle
    Tabella_difesa.h
    Tabella_difesa.cpp
    Tabella_attacco.h
    Tabella_attacco.cpp
)

target_link_libraries(Tabelle
    Ships
)

target_link_libraries(battaglia_navale
    Ships
    Tabelle
)

target_link_libraries(replay
    Ships
    Tabelle
)