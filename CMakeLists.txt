cmake_minimum_required(VERSION 3.12)
project(Qt_OSG_OCC LANGUAGES CXX)

set(OpenCASCADE_LIBRARIES_DIR "C:/Dev_libs/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0/lib")
if (OpenCASCADE_DIR AND EXISTS "${OpenCASCADE_DIR}")
    
else()
    #set(OpenCASCADE_LIBRARIES_DIR "C:/Dev_libs/OpenCASCADE-7.7.0-vc14-64/opencascade-7.7.0/lib")
endif()


set(OSG_ROOT "C:/Dev_libs/OpenSceneGraph-3.6.5")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL)
# lib not has cmake
#find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osg)
find_package(OpenCASCADE REQUIRED)



set(CMAKE_DEBUG_POSTFIX "d")  
if(MSVC)
    set(OSG_LIB_SUFFIX "d")   
endif()


message( STATUS "OSG_ROOT: ${OSG_ROOT}")

set(OSG_INCLUDE_DIR "${OSG_ROOT}/include")
set(OSG_LIB_DIR "${OSG_ROOT}/lib")
include_directories(${OSG_INCLUDE_DIR})
link_directories(${OSG_LIB_DIR})

set(OSG_LIBS
    osg${OSG_LIB_SUFFIX}
    osgViewer${OSG_LIB_SUFFIX}
    osgGA${OSG_LIB_SUFFIX}
    osgUtil${OSG_LIB_SUFFIX}
    osgDB${OSG_LIB_SUFFIX}
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/OsgViewerWidget.h
    src/OsgViewerWidget.cpp
)

message(STATUS "OpenCASCADE_INCLUDE_DIR: ${OpenCASCADE_INCLUDE_DIR}")
if(OpenCASCADE_LIBRARIES)
    list(GET OpenCASCADE_LIBRARIES 0 FIRST_LIB)  # 获取第一个库文件
    get_filename_component(OpenCASCADE_LIBRARIES_DIR "${FIRST_LIB}" DIRECTORY)
    message(STATUS "OpenCASCADE_LIBRARIES_DIR: ${OpenCASCADE_LIBRARIES_DIR}")
endif()
message(STATUS "OpenCASCADE_LIBRARIES: ${OpenCASCADE_LIBRARIES}")

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    TKernel
    TKG3d
    TKMath
    TKBRep
    TKPrim
    TKMesh
    #osg
    #osgViewer
    #osgGA
    #osgUtil
    ${OSG_LIBS} 
)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OpenCASCADE_INCLUDE_DIR}
    ${OPENSCENEGRAPH_INCLUDE_DIR}
)