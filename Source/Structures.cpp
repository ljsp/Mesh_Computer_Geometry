//
// Created by lucas on 18/09/23.
//

#include "Include/Structures.h"

Face::Face(int v0, int v1, int v2, int tri0, int tri1, int tri2)
{
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;

    adjacentTrianglesId[0] = tri0;
    adjacentTrianglesId[1] = tri1;
    adjacentTrianglesId[2] = tri2;

    normal = Point(0, 0, 0);
}

Face::~Face() {

}

Vertex::Vertex(Point p, int triId) : point(p), triangleId(triId) {
    laplacian = 0;
}

Vertex::~Vertex() {

}