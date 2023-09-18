//
// Created by lucas on 18/09/23.
//

#ifndef MESH_COMPUTATIONAL_GEOMETRY_GEOMETRICWORLD_H
#define MESH_COMPUTATIONAL_GEOMETRY_GEOMETRICWORLD_H

#include "Mesh.h"

class GeometricWorld //Generally used to create a singleton instance
{
    QVector<Point> _bBox;  // Bounding box // ou std::vector
public :
    GeometricWorld();
    void draw();
    void drawWireFrame();

    Mesh _mesh;
};



#endif //MESH_COMPUTATIONAL_GEOMETRY_GEOMETRICWORLD_H
