// OSGConvert.cpp
#include "OSGConvert.h"
#include <BRepMesh_IncrementalMesh.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Vec3>
#include <gp_Pnt.hxx>

osg::Node* convertOCCShapeToOSG(const TopoDS_Shape& shape) {

    BRepMesh_IncrementalMesh mesher(shape, 0.1); 

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES);

    unsigned int vertexOffset = 0;

    TopExp_Explorer faceExplorer(shape, TopAbs_FACE);
    for (; faceExplorer.More(); faceExplorer.Next()) {
        const TopoDS_Face& face = TopoDS::Face(faceExplorer.Current());

        TopLoc_Location loc;
        Handle_Poly_Triangulation triangulation = BRep_Tool::Triangulation(face, loc);
        if (triangulation.IsNull()) {
            continue;
        }


        Standard_Integer nbNodes = triangulation->NbNodes();
        for (Standard_Integer i = 1; i <= nbNodes; ++i)
        {
            gp_Pnt pnt = triangulation->Node(i);
            vertices->push_back(osg::Vec3(pnt.X(), pnt.Y(), pnt.Z()));
            std::cout << "Node " << i << ": " << pnt.X() << ", " << pnt.Y() << ", " << pnt.Z() << std::endl;
        }

        const Poly_Array1OfTriangle& triangles = triangulation->Triangles();
        for (int i = triangles.Lower(); i <= triangles.Upper(); ++i) {
            int n1, n2, n3;
            triangles(i).Get(n1, n2, n3);

            indices->push_back(vertexOffset + n1 - 1);
            indices->push_back(vertexOffset + n2 - 1);
            indices->push_back(vertexOffset + n3 - 1);
        }

        
        vertexOffset += nbNodes;
    }

    geometry->setVertexArray(vertices);
    geometry->addPrimitiveSet(indices);
    geode->addDrawable(geometry);

    return geode.release();
}
