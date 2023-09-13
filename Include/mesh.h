#ifndef MESH_H
#define MESH_H

#include <QOpenGLWidget>

// TO MODIFY
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

class Mesh
{
public:
    Mesh();
    ~Mesh();
    void drawMesh();
    void drawMeshWireFrame();
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
private:
    std::map<std::pair<int,int>,std::pair<int,int>> map;
};

class GeometricWorld //Generally used to create a singleton instance
{
    QVector<Point> _bBox;  // Bounding box // ou std::vector
public :
    GeometricWorld();
    void draw();
    void drawWireFrame();

    Mesh _mesh;
};


#endif // MESH_H