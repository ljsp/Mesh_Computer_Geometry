cmake_minimum_required(VERSION 3.19)

project(Mesh_Computational_Geometry)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Qt6_DIR "/usr/local/Qt/6.5.2/gcc_64/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS Core Gui OpenGLWidgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_DIR Source)
set(INC_DIR Include)
set(UI_DIR UI)

set(SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/mainwindow.cpp
        ${SRC_DIR}/gldisplaywidget.cpp
        ${SRC_DIR}/mesh.cpp
)

set(HEADERS
        ${INC_DIR}/mainwindow.h
        ${INC_DIR}/gldisplaywidget.h
        ${INC_DIR}/mesh.h
)
qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})


target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGLWidgets
    GL
    GLU
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
qt_finalize_executable(${PROJECT_NAME})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glu32 opengl32)
endif()

