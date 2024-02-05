qt_add_executable(BodyMonitoringQt
    main.cpp
)

target_link_libraries(BodyMonitoringQt PRIVATE 
    XyModel
    bmDbModel
    bmUi
    Qt6::Sql
    Qt6::Widgets
    Qt6::Charts
    Qt6::Multimedia
)

set_target_properties(BodyMonitoringQt PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
