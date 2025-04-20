// OSGConvert.h
#pragma once
#include <TopoDS_Shape.hxx>
#include <osg/Node>

osg::Node* convertOCCShapeToOSG(const TopoDS_Shape& shape);

// OSGConvert.cpp
#include "OSGConvert.h"
#include <BRepMesh_IncrementalMesh.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <osg/Geometry>
#include <osg/Geode>

osg::Node* convertOCCShapeToOSG(const TopoDS_Shape& shape) {
    
    BRepMesh_IncrementalMesh mesher(shape, 0.1);  


    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES);


    TopExp_Explorer faceExplorer(shape, TopAbs_FACE);
    for (; faceExplorer.More(); faceExplorer.Next()) {
        //const TopoDS_Face& face = TopoDS::Face(faceExplorer.Current());

    }

    geometry->setVertexArray(vertices);
    geometry->addPrimitiveSet(indices);
    geode->addDrawable(geometry);
    return geode.release();
}