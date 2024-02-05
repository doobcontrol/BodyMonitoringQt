qt_add_library(bmUi STATIC
    bmDataShow.cpp
    bmMainWin.cpp
    bmReader.cpp
    EquManageWin.cpp
    frmAlertSet.cpp
    MonitorInfoPanel.cpp
    xyTableModel.cpp
    xyTableView.cpp
)

qt_add_resources(bmUi bmresources
    PREFIX "/"
    BASE "images"
    FILES 
        images/Exit.png
        images/Main.png
        images/Start.png
        images/Loading.png
        images/Stop.png
        images/New.png
        images/Edit.png
        images/Delete.png
        images/House.png
        images/fullscreen.png
        images/normalscreen.png
        images/monitorobj.png
        images/photoicon.png
        images/alertset.png
        images/alert.gif
        images/alerm.wav
        images/startrecord.png
        images/stoprecord.png
        images/qtbase_zh_CN.qm
)

target_link_libraries(bmUi PRIVATE 
    XyModel
    bmDbModel
    Qt6::Sql
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::Charts
    Qt6::Multimedia
)

target_include_directories(bmUi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
