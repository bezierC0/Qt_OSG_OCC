// OSGConvert.cpp

#include <BRepMesh_IncrementalMesh.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Vec3>
#include <gp_Pnt.hxx>

osg::Node* convertOCCShapeToOSG(const TopoDS_Shape& shape) ;