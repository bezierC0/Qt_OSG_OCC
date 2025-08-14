# Qt_OSG_OCC-main

这是一个演示OpenCASCADE Technology (OCC)、OpenSceneGraph (OSG) 和 Qt 集成的简单项目。它提供了一个基本的3D查看器，能够加载和显示由OpenCASCADE处理并使用OSG在Qt应用程序中渲染的CAD模型（特别是STEP文件）。

## 主要功能

*   **OpenCASCADE 集成：** 利用OpenCASCADE读取和处理CAD几何体（例如STEP文件）。
*   **OpenSceneGraph (OSG) 渲染：** 使用OSG渲染3D模型，提供高效的可视化功能。
*   **Qt 框架：** 为应用程序提供图形用户界面（GUI）。
*   **交互式查看器：** 支持使用鼠标和键盘进行基本的相机操作（平移、缩放、旋转）。

## 使用的技术

*   Qt
*   OpenCASCADE Technology (OCC)
*   OpenSceneGraph (OSG)

## 编译说明

本项目使用CMake作为构建系统。要编译本项目，请按照以下步骤操作：

1.  **先决条件：** 确保您的系统上安装了以下库：
    *   Qt（例如Qt 5或Qt 6）
    *   OpenCASCADE Technology (OCC)
    *   OpenSceneGraph (OSG)
    *   CMake
    *   C++ 编译器（例如GCC、MSVC）

2.  **构建步骤：**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    在Windows上，您可能需要指定生成器，例如：
    ```bash
    cmake .. -G "Visual Studio 17 2022"
    cmake --build . --config Release
