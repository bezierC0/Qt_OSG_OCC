#include "OsgViewerWidget.h"
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <BRepPrimAPI_MakeBox.hxx>
#include <OSGConvert.h>
#include <osgGA/TrackballManipulator>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>

static osg::GraphicsContext* createGraphicsContext(QOpenGLWidget* widget)
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 0;
    traits->y = 0;
    traits->width = widget->width();
    traits->height = widget->height();
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = nullptr;

    traits->inheritedWindowData = new osgViewer::GraphicsWindowWin32::WindowData((HWND)widget->winId());

    return new osgViewer::GraphicsWindowEmbedded(traits.get());
}

OsgViewerWidget::OsgViewerWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setMinimumSize(100, 100);
    viewer = new osgViewer::Viewer;
    root = new osg::Group;
}

OsgViewerWidget::~OsgViewerWidget() = default;

osg::Node* OsgViewerWidget::createBoxFromOCC()
{
#if 0
    BRepPrimAPI_MakeBox makeBox(100.0, 100.0, 100.0);
    TopoDS_Shape boxShape = makeBox.Shape();


    osg::ref_ptr<osg::Node> node = convertOCCShapeToOSG(boxShape); 

    return node.release();
#endif
    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3(0, 0, 0), 100.0f);

    osg::ref_ptr<osg::ShapeDrawable> boxDrawable = new osg::ShapeDrawable(box);


    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(boxDrawable);

    return geode.release();
}

void OsgViewerWidget::createOsgViewer()
{

    osg::GraphicsContext* gc = createGraphicsContext(this);

    osg::Camera* camera = viewer->getCamera();
    camera->setGraphicsContext(gc);
    camera->setViewport(0, 0, width(), height());
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width()) / height(), 1.0, 10000.0);

    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;

    manipulator->setHomePosition(
        osg::Vec3(0, -300, 200), 
        osg::Vec3(0, 0, 0),     
        osg::Vec3(0, 0, 1)       
    );
    viewer->setCameraManipulator(manipulator);

    viewer->setSceneData(root);

    viewer->home();
}

void OsgViewerWidget::initializeGL()
{
    createOsgViewer();

    osg::Node* boxNode = createBoxFromOCC();
    if (boxNode)
    {
        root->addChild(boxNode);
    }

    osg::ref_ptr<osg::Light> light = new osg::Light;
    light->setLightNum(0);
    light->setPosition(osg::Vec4(0.0f, -300.0f, 300.0f, 1.0f));
    light->setDiffuse(osg::Vec4(1, 1, 1, 1));

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
    lightSource->setLight(light);

    root->addChild(lightSource);
}

void OsgViewerWidget::paintGL()
{
    if (viewer.valid())
    {
        viewer->frame();
        update();  
    }
}

void OsgViewerWidget::resizeGL(int width, int height)
{
    if (viewer.valid() && viewer->getCamera())
    {
        viewer->getCamera()->setViewport(0, 0, width, height);
    }
}

void OsgViewerWidget::mousePressEvent(QMouseEvent* event)
{
    viewer->getEventQueue()->mouseButtonPress(static_cast<float>(event->x()), static_cast<float>(event->y()), event->button());
}

void OsgViewerWidget::mouseReleaseEvent(QMouseEvent* event)
{
    viewer->getEventQueue()->mouseButtonRelease(static_cast<float>(event->x()), static_cast<float>(event->y()), event->button());
}

void OsgViewerWidget::mouseMoveEvent(QMouseEvent* event)
{
    viewer->getEventQueue()->mouseMotion(static_cast<float>(event->x()), static_cast<float>(event->y()));
}

void OsgViewerWidget::wheelEvent(QWheelEvent* event)
{
    viewer->getEventQueue()->mouseScroll(
        event->angleDelta().y() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP
        : osgGA::GUIEventAdapter::SCROLL_DOWN);
}

void OsgViewerWidget::keyPressEvent(QKeyEvent* event)
{
    viewer->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol)event->key());
}

void OsgViewerWidget::keyReleaseEvent(QKeyEvent* event)
{
    viewer->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol)event->key());
}
