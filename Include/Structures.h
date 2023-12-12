//
// Created by lucas on 18/09/23.
//

#ifndef MESH_COMPUTATIONAL_GEOMETRY_STRUCTURES_H
#define MESH_COMPUTATIONAL_GEOMETRY_STRUCTURES_H

#include <vector>

class Point
{
public:
    double _x;
    double _y;
    double _z;

    Point():_x(),_y(),_z() {}
    Point(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_) {}
    Point(const Point& p):_x(p._x),_y(p._y),_z(p._z) {}

    Point  operator+  (const Point& p) const { return Point(_x+p._x,_y+p._y,_z+p._z); }
    Point  operator-  (const Point& p) const { return Point(_x-p._x,_y-p._y,_z-p._z); }
    Point  operator*  (double d)       const { return Point(_x*d,_y*d,_z*d); }
    Point  operator/  (double d)       const { return Point(_x/d,_y/d,_z/d); }
    Point& operator=  (const Point& p)       { _x=p._x; _y=p._y; _z=p._z; return *this; }
    Point& operator+= (const Point& p)       { _x+=p._x; _y+=p._y; _z+=p._z; return *this; }
    Point& operator-= (const Point& p)       { _x-=p._x; _y-=p._y; _z-=p._z; return *this; }
    Point& operator*= (double d)             { _x*=d; _y*=d; _z*=d; return *this; }
    Point& operator/= (double d)             { _x/=d; _y/=d; _z/=d; return *this; }
    bool   operator== (const Point& p) const { return (_x==p._x && _y==p._y && _z==p._z); }
    bool   operator!= (const Point& p) const { return (_x!=p._x || _y!=p._y || _z!=p._z); }

    ~Point() {}

};

class Face {
public:
    Face(int v1, int v2, int v3, int tri1 = -1, int tri2=-1,int tri3=-1, bool visible = true);
    ~Face();
    int vertices[3];
    int adjacentTrianglesId[3];
    Point normal;
    bool isVisible;
    bool containsVertex(int vertexIndex) const;
    int getThirdVertex(int vertexA, int vertexB) const;
private:
};

class Vertex {
public:
    Vertex(Point p, int triId = -1);
    ~Vertex();
    Point point;
    int triangleId;
    Point laplacian;
private:
};

#endif //MESH_COMPUTATIONAL_GEOMETRY_STRUCTURES_H
