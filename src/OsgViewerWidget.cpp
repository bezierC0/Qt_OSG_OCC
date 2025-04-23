#include "OsgViewerWidget.h"
#include <QFileDialog>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <BRepPrimAPI_MakeBox.hxx>
#include <STEPControl_Reader.hxx>
#include <BRepBndLib.hxx>
#include <OSGConvert.h>
#include <BRepExtrema_DistShapeShape.hxx>
#include <osgGA/TrackballManipulator>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <BRepAlgoAPI_Common.hxx>


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

OsgViewerWidget::OsgViewerWidget()
{
}

OsgViewerWidget::OsgViewerWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setMinimumSize(100, 100);
    m_viewer = new osgViewer::Viewer;
    m_root = new osg::Group;
}

OsgViewerWidget::~OsgViewerWidget() = default;

osg::Node* OsgViewerWidget::createTestShape()
{
    std::string stepFilePath = R"(C:\Workspace\TestData\step\screw.step)";
    const QString filePath = QFileDialog::getOpenFileName(this, "Open STEP File", "", "STEP Files (*.step *.stp)");
    if (filePath.isEmpty())
        return nullptr;
    stepFilePath = filePath.toStdString();

    STEPControl_Reader reader;
    const IFSelect_ReturnStatus status = reader.ReadFile(stepFilePath.c_str());

    if (status != IFSelect_RetDone)
    {
        std::cerr << "Failed to read STEP file: " << stepFilePath << std::endl;
        return nullptr;
    }

    bool failTransfer = (reader.TransferRoots() == 0);
    if (failTransfer)
    {
        std::cerr << "Failed to transfer STEP file shapes." << std::endl;
        return nullptr;
    }

    TopoDS_Shape shape = reader.OneShape();

    std::vector<TopoDS_Shape> parts;
    for ( TopExp_Explorer exp( shape, TopAbs_SOLID ); exp.More(); exp.Next() ) {
      TopoDS_Shape part = exp.Current();
      if ( !part.IsNull() )
        parts.push_back( part );
    }

    if ( parts.size() < 2 ) {
      std::cerr << "Only one part found. No interference check needed." << std::endl;
    }

    osg::ref_ptr<osg::Group> rootNode = new osg::Group();
    osg::ref_ptr<osg::Node> partNode = convertOCCShapeToOSG( shape );
    rootNode->addChild( partNode );

    /*for ( size_t i = 0; i < parts.size(); ++i ) {

      osg::ref_ptr<osg::Node> partNode = convertOCCShapeToOSG( parts[i] );
      if ( partNode ) {
        rootNode->addChild( partNode );
      }
    }*/

    for ( size_t i = 0; i < parts.size(); ++i ) {
      for ( size_t j = i + 1; j < parts.size(); ++j ) {

        Bnd_Box box1, box2;
        BRepBndLib::Add( parts[i], box1 );
        BRepBndLib::Add( parts[j], box2 );
        if ( !box1.IsOut( box2 ) ) {

          BRepExtrema_DistShapeShape dist( parts[i], parts[j] );
          dist.Perform();
          if ( dist.IsDone() && dist.Value() < 1e-6 ) 
          {
            std::cout << "Part " << i << " and Part " << j << " collide or touch!" << std::endl;

  
            //BRepAlgoAPI_Common common( parts[i], parts[j] );
            //common.Build();
            //if ( !common.Shape().IsNull() ) {
            //  osg::ref_ptr<osg::Node> collisionNode = convertOCCShapeToOSG( common.Shape(), osg::Vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
            //  if ( collisionNode )
            //    rootNode->addChild( collisionNode );
            //}
          }
        }
      }
    }

    return rootNode.release();
}

osg::Node* OsgViewerWidget::createBoxFromOCC()
{

    BRepPrimAPI_MakeBox makeBox(100.0, 100.0, 100.0);
    TopoDS_Shape boxShape = makeBox.Shape();

    osg::ref_ptr<osg::Node> node = convertOCCShapeToOSG(boxShape); 

    return node.release();
}

void OsgViewerWidget::createOsgViewer()
{
    osg::GraphicsContext* gc = createGraphicsContext(this);

    osg::Camera* camera = m_viewer->getCamera();
    camera->setGraphicsContext(gc);
    camera->setViewport(0, 0, width(), height());
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width()) / height(), 1.0, 10000.0);

    m_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;

    manipulator->setHomePosition(
        osg::Vec3(0, -300, 200), 
        osg::Vec3(0, 0, 0),     
        osg::Vec3(0, 0, 1)       
    );
    m_viewer->setCameraManipulator(manipulator);

    m_viewer->setSceneData(m_root);

    m_viewer->home();
}

void OsgViewerWidget::initializeGL()
{
    createOsgViewer();

    //osg::Node* boxNode = createBoxFromOCC();
    osg::Node* boxNode = createTestShape();
    if (boxNode)
    {
        m_root->addChild(boxNode);
    }

    osg::ref_ptr<osg::Light> light = new osg::Light;
    light->setLightNum(0);
    light->setPosition(osg::Vec4(0.0f, -300.0f, 300.0f, 1.0f));
    light->setDiffuse(osg::Vec4(1, 1, 1, 1));

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
    lightSource->setLight(light);

    m_root->addChild(lightSource);
}

void OsgViewerWidget::paintGL()
{
    if (m_viewer.valid())
    {
        m_viewer->frame();
        update();  
    }
}

void OsgViewerWidget::resizeGL(int width, int height)
{
    if (m_viewer.valid() && m_viewer->getCamera())
    {
        m_viewer->getCamera()->setViewport(0, 0, width, height);
    }
}

void OsgViewerWidget::mousePressEvent(QMouseEvent* event)
{
    m_viewer->getEventQueue()->mouseButtonPress(static_cast<float>(event->x()), static_cast<float>(event->y()), event->button());
}

void OsgViewerWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_viewer->getEventQueue()->mouseButtonRelease(static_cast<float>(event->x()), static_cast<float>(event->y()), event->button());
}

void OsgViewerWidget::mouseMoveEvent(QMouseEvent* event)
{
    m_viewer->getEventQueue()->mouseMotion(static_cast<float>(event->x()), static_cast<float>(event->y()));
}

void OsgViewerWidget::wheelEvent(QWheelEvent* event)
{
    m_viewer->getEventQueue()->mouseScroll(
        event->angleDelta().y() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP
        : osgGA::GUIEventAdapter::SCROLL_DOWN);
}

void OsgViewerWidget::keyPressEvent(QKeyEvent* event)
{
    m_viewer->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol)event->key());
}

void OsgViewerWidget::keyReleaseEvent(QKeyEvent* event)
{
    m_viewer->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol)event->key());
}
