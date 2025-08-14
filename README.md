# Qt_OSG_OCC-main

This is a simple project demonstrating the integration of OpenCASCADE Technology (OCC), OpenSceneGraph (OSG), and Qt. It provides a basic 3D viewer capable of loading and displaying CAD models (specifically STEP files) processed by OpenCASCADE and rendered using OSG within a Qt application.

[English](./README.md) | [简体中文](./README.zh_CN.md) | [日本語](./README.ja_JP.md)

## Key Features

*   **OpenCASCADE Integration:** Utilizes OpenCASCADE for reading and processing CAD geometries (e.g., STEP files).
*   **OpenSceneGraph (OSG) Rendering:** Renders the 3D models using OSG, providing efficient visualization capabilities.
*   **Qt Framework:** Provides the graphical user interface (GUI) for the application.
*   **Interactive Viewer:** Supports basic camera manipulation (pan, zoom, rotate) using mouse and keyboard.

## Technologies Used

*   Qt
*   OpenCASCADE Technology (OCC)
*   OpenSceneGraph (OSG)

## Compilation Instructions

This project uses CMake for its build system. To compile the project, follow these steps:

1.  **Prerequisites:** Ensure you have the following libraries installed on your system:
    *   Qt (e.g., Qt 5 or Qt 6)
    *   OpenCASCADE Technology (OCC)
    *   OpenSceneGraph (OSG)
    *   CMake
    *   A C++ compiler (e.g., GCC, MSVC)

2.  **Build Steps:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    On Windows, you might need to specify the generator, for example:
    ```bash
    cmake .. -G "Visual Studio 17 2022"
    cmake --build . --config Release

