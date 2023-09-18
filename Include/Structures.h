//
// Created by lucas on 18/09/23.
//

#ifndef MESH_COMPUTATIONAL_GEOMETRY_STRUCTURES_H
#define MESH_COMPUTATIONAL_GEOMETRY_STRUCTURES_H

class Point
{
public:
    double _x;
    double _y;
    double _z;

    Point():_x(),_y(),_z() {}
    Point(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_) {}
};

class Face {
public:
    Face(int v1, int v2, int v3, int tri1, int tri2, int tri3);
    ~Face();
    int vertices[3];
    int adjacentTrianglesId[3];
private:
};

class Vertex {
public:
    Vertex(Point p, int triId);
    ~Vertex();
    Point point;
    int triangleId;
private:
};

#endif //MESH_COMPUTATIONAL_GEOMETRY_STRUCTURES_H