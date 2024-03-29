cmake_minimum_required(VERSION 3.22.1)
project(3DReceiver)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# We need to add .h files (at least those that define a custom Qt class), see https://stackoverflow.com/a/14011060
qt_add_executable(${PROJECT_NAME}
                    src/main.cpp src/MyWindow.cpp src/input_data.cpp src/network.cpp src/worker.cpp
                    include/MyWindow.h include/input_data.hpp include/network.hpp include/worker.hpp
                    include/template.ui
                 )
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)
target_include_directories(${PROJECT_NAME} PUBLIC include)


target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Widgets)
