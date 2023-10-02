cmake_minimum_required(VERSION 3.19)

project(Mesh_Computational_Geometry)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Qt6_DIR "/home/lucas/Qt/6.5.3/gcc_64/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS Core Gui OpenGLWidgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_DIR Source)
set(INC_DIR Include)
set(UI_DIR UI)

set(SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/MainWindow.cpp
        ${SRC_DIR}/glDisplayWidget.cpp
        ${SRC_DIR}/Mesh.cpp
        ${SRC_DIR}/GeometricWorld.cpp
        ${SRC_DIR}/Structures.cpp
)

set(HEADERS
        ${INC_DIR}/MainWindow.h
        ${INC_DIR}/glDisplayWidget.h
        ${INC_DIR}/Mesh.h
        ${INC_DIR}/GeometricWorld.h
        ${INC_DIR}/Structures.h
        ${INC_DIR}/Utils.h
        ${INC_DIR}/Mathematics.h
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

