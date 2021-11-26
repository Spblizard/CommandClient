cmake_minimum_required(VERSION 3.5)

project(CommandClient)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5 COMPONENTS Core Network Gui Quick)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    res/qml.qrc
    src/client.cpp
    src/client.h
)

target_link_libraries(${PROJECT_NAME} 
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    Qt5::Quick
)
