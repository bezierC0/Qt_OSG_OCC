#pragma once
#include <QOpenGLWidget>
#include <qevent.h>
#include <osgViewer/Viewer>
#include <osg/Group>

class OsgViewerWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    OsgViewerWidget() = default;
    explicit OsgViewerWidget(QWidget* parent = nullptr);
    ~OsgViewerWidget() override;

    osg::Node* createBoxFromOCC();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void OsgViewerWidget::mousePressEvent(QMouseEvent* event) override;
    void OsgViewerWidget::mouseReleaseEvent(QMouseEvent* event)override;
    void OsgViewerWidget::mouseMoveEvent(QMouseEvent* event)override;
    void OsgViewerWidget::wheelEvent(QWheelEvent* event)override;
    void OsgViewerWidget::keyPressEvent(QKeyEvent* event)override;
    void OsgViewerWidget::keyReleaseEvent(QKeyEvent* event)override;

private:
    osg::ref_ptr<osgViewer::Viewer> viewer; 
    osg::ref_ptr<osg::Group> root;
    void createOsgViewer();  

};