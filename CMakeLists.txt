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

install(TARGETS BodyMonitoringQt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
#for desktop
SET(DDM_DESKTOP_DIR "/usr/share/applications")
SET(DDM_PIXMAPS_DIR "/usr/share/icons")
INSTALL(FILES src/mainapp/BodyMonitoringQt.desktop DESTINATION ${DDM_DESKTOP_DIR})
INSTALL(FILES src/mainapp/BodyMonitoringQt.png DESTINATION ${DDM_PIXMAPS_DIR})

qt_generate_deploy_app_script(
    TARGET BodyMonitoringQt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

set(CPACK_PACKAGE_NAME BodyMonitoringQt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BodyMonitoringQt - 封闭式房间单人生命监测系统")
set(CPACK_PACKAGE_VENDOR "XySoft")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES ON)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local/BodyMonitoringQt")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "XySoft <XySoft@example.com>")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/mainapp/BodyMonitoringQt.png") 
set(CPACK_GENERATOR "DEB")
include(CPack)
