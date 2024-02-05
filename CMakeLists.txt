cmake_minimum_required(VERSION 3.16)

project(BodyMonitoringQt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(CMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH "/home/dooacontrol/Qt/6.6.1/gcc_64/lib/cmake")
message(CMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}")
find_package(Qt6 REQUIRED COMPONENTS 
    Widgets
    Sql
    SerialPort
    Charts
    Multimedia
)
qt_standard_project_setup()

add_subdirectory(src/dbModel)
add_subdirectory(src/mainapp)
add_subdirectory(src/ui)
add_subdirectory(src/xyModel)
