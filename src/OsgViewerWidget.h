#pragma once
#include <QOpenGLWidget>
#include <qevent.h>
#include <osgViewer/Viewer>
#include <osg/Group>

class OsgViewerWidget 
    : public QOpenGLWidget 
{
    Q_OBJECT
public:
    OsgViewerWidget();
    explicit OsgViewerWidget(QWidget* parent = nullptr);
    ~OsgViewerWidget() override;

    osg::Node* createTestShape();
    osg::Node* createBoxFromOCC();


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    osg::ref_ptr<osgViewer::Viewer> m_viewer; 
    osg::ref_ptr<osg::Group> m_root;
    void createOsgViewer();  

};