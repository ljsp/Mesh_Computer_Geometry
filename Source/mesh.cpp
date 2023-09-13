#include <QVector3D>
#include "Include/mesh.h"

GeometricWorld::GeometricWorld()
{
    double width=0.5, depth=0.6, height=0.8;
    _bBox.push_back(Point(-0.5*width,-0.5*depth,-0.5*height)); //0
    _bBox.push_back(Point(-0.5*width,0.5*depth,-0.5*height)); // 1
    _bBox.push_back(Point(0.5*width,-0.5*depth,-0.5*height)); // 2
    _bBox.push_back(Point(-0.5*width,-0.5*depth,0.5*height)); // 3
}

// The following functions could be displaced into a module OpenGLDisplayGeometricWorld that would include mesh.h

// Draw a Point
void glPointDraw(const Point & p) {
    glVertex3f(p._x, p._y, p._z);
}

//Example with a bBox
void GeometricWorld::draw() {
    glColor3d(1,0,0);
    glBegin(GL_TRIANGLES);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[1]);
    glPointDraw(_bBox[2]);
    glEnd();

    glColor3d(0,1,0);
    glBegin(GL_TRIANGLES);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[2]);
    glPointDraw(_bBox[3]);
    glEnd();

    glColor3d(0,0,1);
    glBegin(GL_TRIANGLES);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[3]);
    glPointDraw(_bBox[1]);
    glEnd();

    //glColor3d(1,1,0);
}

//Example with a wireframe bBox
void GeometricWorld::drawWireFrame() {
    glColor3d(0,1,0);
    glBegin(GL_LINE_STRIP);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[1]);
    glEnd();
    glColor3d(0,0,1);
    glBegin(GL_LINE_STRIP);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[2]);
    glEnd();
    glColor3d(1,0,0);
    glBegin(GL_LINE_STRIP);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[3]);
    glEnd();
}

Face::Face(int v0, int v1, int v2, int tri0, int tri1, int tri2)
{
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;

    adjacentTrianglesId[0] = tri0;
    adjacentTrianglesId[1] = tri1;
    adjacentTrianglesId[2] = tri2;
}

Face::~Face() {

}

Vertex::Vertex(Point p, int triId) : point(p), triangleId(triId) {

}

Vertex::~Vertex() {

}

Mesh::Mesh() {
    double width=0.5, depth=0.6, height=0.8;
    Point a(-0.5*width,-0.5*depth,-0.5*height);
    Point b(-0.5*width,0.5 *depth,-0.5*height);
    Point c(0.5*width ,-0.5*depth,-0.5*height);
    Point d(-0.5*width,-0.5*depth, 0.5*height);

    vertices.push_back(Vertex(a, 0)); // 0
    vertices.push_back(Vertex(b, 1)); // 1
    vertices.push_back(Vertex(c, 2)); // 2
    vertices.push_back(Vertex(d, 3)); // 3

    faces.push_back(Face(0, 3, 2, 2, 3, 4));
    faces.push_back(Face(0, 1, 3, 1, 3, 4));
    faces.push_back(Face(2, 3, 1, 1, 2, 4));
    faces.push_back(Face(2, 1, 0, 2, 3, 4));
}

void Mesh::drawMesh() {
    int colors[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0};
    for(int i = 0; i < faces.size(); i++) {
        glColor3d(colors[i * 3],colors[i * 3 + 1],colors[i * 3 +2]);
        glBegin(GL_TRIANGLES);
        glPointDraw(vertices.at(faces[i].vertices[0]).point);
        glPointDraw(vertices.at(faces[i].vertices[1]).point);
        glPointDraw(vertices.at(faces[i].vertices[2]).point);
        glEnd();
    }
}

void Mesh::drawMeshWireFrame() {
    int colors[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0};
    for(int i = 0; i < faces.size(); i++) {
        glColor3d(colors[i * 3],colors[i * 3 + 1],colors[i * 3 +2]);
        for (int j = 0; j < 3; j++) {
            glBegin(GL_LINE_STRIP);
            glPointDraw(vertices.at(faces[i].vertices[j]).point);
            glPointDraw(vertices.at(faces[i].vertices[j+1%3]).point);
            glEnd();
        }
    }
}

Mesh::~Mesh() {
}