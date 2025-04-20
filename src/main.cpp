#include <QApplication>
#include <QMainWindow>
#include "OsgViewerWidget.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QMainWindow window;
    auto* osgWidget = new OsgViewerWidget(&window);
    window.setCentralWidget(osgWidget);
    window.resize(800, 600);
    window.show();

    return app.exec();
}