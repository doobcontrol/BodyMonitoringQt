qt_add_library(bmDbModel STATIC
    bmRecord.cpp
    bmRecordItem.cpp
    ConfigPars.cpp
    EquMonitorObj.cpp
    MonitorPerson.cpp
    MonitorRoom.cpp
)
target_link_libraries(bmDbModel PRIVATE 
    XyModel
    Qt6::Sql
)
target_include_directories(bmDbModel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
