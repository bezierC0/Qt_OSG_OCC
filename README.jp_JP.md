# Qt_OSG_OCC-main

これは、OpenCASCADE Technology (OCC)、OpenSceneGraph (OSG)、およびQtの統合を示すシンプルなプロジェクトです。Qtアプリケーション内でOpenCASCADEによって処理され、OSGを使用してレンダリングされたCADモデル（特にSTEPファイル）をロードおよび表示できる基本的な3Dビューアを提供します。

## 主な機能

*   **OpenCASCADE 統合：** OpenCASCADEを利用してCADジオメトリ（例：STEPファイル）を読み込み、処理します。
*   **OpenSceneGraph (OSG) レンダリング：** OSGを使用して3Dモデルをレンダリングし、効率的な視覚化機能を提供します。
*   **Qt フレームワーク：** アプリケーションのグラフィカルユーザーインターフェース（GUI）を提供します。
*   **インタラクティブビューア：** マウスとキーボードを使用した基本的なカメラ操作（パン、ズーム、回転）をサポートします。

## 使用技術

*   Qt
*   OpenCASCADE Technology (OCC)
*   OpenSceneGraph (OSG)

## コンパイル手順

このプロジェクトはCMakeをビルドシステムとして使用しています。プロジェクトをコンパイルするには、以下の手順に従ってください。

1.  **前提条件：** システムに以下のライブラリがインストールされていることを確認してください。
    *   Qt（例：Qt 5またはQt 6）
    *   OpenCASCADE Technology (OCC)
    *   OpenSceneGraph (OSG)
    *   CMake
    *   C++ コンパイラ（例：GCC、MSVC）

2.  **ビルド手順：**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    Windowsでは、ジェネレータを指定する必要がある場合があります。例：
    ```bash
    cmake .. -G "Visual Studio 17 2022"
    cmake --build . --config Release
