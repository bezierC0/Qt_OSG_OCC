cmake_minimum_required(VERSION 3.12)
project(Qt_OSG_OCC VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Qt_OSG_OCC_LinkDirectories)   # include path list
set(Qt_OSG_OCC_LinkLibraries)     # library list

### Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL)
if(Qt5_FOUND)
    list(APPEND Qt_OSG_OCC_LinkLibraries Qt5::Widgets Qt5::OpenGL)
else()
    message(STATUS "Qt5 not found")
endif()

### OpenSceneGraph
set(CMAKE_DEBUG_POSTFIX "d")
if(MSVC)
    set(OSG_LIB_SUFFIX "d")
endif()

if (OSG_ROOT AND EXISTS "${OSG_ROOT}")
    message(STATUS "OSG_ROOT: ${OSG_ROOT}")
    set(OSG_INCLUDE_DIR "${OSG_ROOT}/include")
    set(OSG_LIB_DIR "${OSG_ROOT}/lib")
    
    list(APPEND Qt_OSG_OCC_LinkDirectories ${OSG_INCLUDE_DIR})
    
    link_directories(${OSG_LIB_DIR})
    set(OSG_LIBS
        osg${OSG_LIB_SUFFIX}
        osgViewer${OSG_LIB_SUFFIX}
        osgGA${OSG_LIB_SUFFIX}
        osgUtil${OSG_LIB_SUFFIX}
        osgDB${OSG_LIB_SUFFIX}
    )
    list(APPEND Qt_OSG_OCC_LinkLibraries ${OSG_LIBS})
else()
    message(STATUS "OSG_ROOT not found")
endif()

### OpenCASCADE
if (OpenCASCADE_DIR AND EXISTS "${OpenCASCADE_DIR}")
    message(STATUS "OpenCASCADE_DIR: ${OpenCASCADE_DIR}")
    set(OpenCASCADE_INCLUDE_DIR "${OpenCASCADE_DIR}/inc")
    set(OpenCASCADE_LIB_DIR "${OpenCASCADE_DIR}/lib")
    
    list(APPEND Qt_OSG_OCC_LinkDirectories ${OpenCASCADE_INCLUDE_DIR})
    
    link_directories(${OpenCASCADE_LIB_DIR})
    list(APPEND Qt_OSG_OCC_LinkLibraries
        TKernel
        TKG3d
        TKMath
        TKBRep
        TKPrim
        TKMesh
    )
else()
    message(STATUS "OpenCASCADE_DIR not found")
endif()

### Executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/OsgViewerWidget.h
    src/OsgViewerWidget.cpp
)

### Apply collected libraries and include dirs
target_link_libraries(${PROJECT_NAME} PRIVATE ${Qt_OSG_OCC_LinkLibraries})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Qt_OSG_OCC_LinkDirectories}
)
