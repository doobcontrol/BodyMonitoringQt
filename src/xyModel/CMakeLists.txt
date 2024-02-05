qt_add_library(XyModel STATIC
    dbHelper.cpp
    XyBaseModel.cpp
    XyKModel.cpp
)
target_link_libraries(XyModel PRIVATE Qt6::Sql)
target_include_directories(XyModel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
