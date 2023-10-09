#ifndef MESH_H
#define MESH_H

#include <QOpenGLWidget>
#include "Structures.h"
#include "Mathematics.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();
    void drawMesh(int drawMode);
    void drawMeshWireFrame();
    void drawTriangle(int i, double r, double g, double b);
    void drawInfPoint();

    void initializeIteratorsAndCirulators();
    void saveOFF(QString filename);
    void loadOFF(const char* filename, bool isTriangulated);

    void insertMap(std::pair<int,int> edge, int faceId, int sommetId);
    static std::pair<int,int> edge(int v1, int v2);

    void flipEdge(int face0, int face1);
    void findCommonEdge(int face0, int face1, int &sharedPoint1, int &sharedPoint2, int &uniquePointF0, int &uniquePointF1);
    double orientationTest(Point a, Point b, Point c);
    bool inTriangle(int triId, Point p);
    void splitTriangle(int face, Point p);

    struct Iterator_on_vertices {
        std::vector<Vertex>::iterator it;
        Iterator_on_vertices() = default;
        explicit Iterator_on_vertices(std::vector<Vertex>::iterator it_) : it(it_) {}
        Iterator_on_vertices& operator++() { ++it; return *this; }
        bool operator!=(const Iterator_on_vertices& other) const { return it != other.it; }
        Vertex& operator*() { return *it; }
    };
    Iterator_on_vertices vertices_begin() { return Iterator_on_vertices(vertices.begin()); }
    Iterator_on_vertices vertices_past_the_end() { return Iterator_on_vertices(vertices.end()); }

    struct Iterator_on_faces {
        std::vector<Face>::iterator it;
        Iterator_on_faces() = default;
        explicit Iterator_on_faces(std::vector<Face>::iterator it_) : it(it_) {}
        Iterator_on_faces& operator++() { ++it; return *this; }
        Iterator_on_faces& operator--() { --it; return *this; }
        bool operator!=(const Iterator_on_faces& other) const { return it != other.it; }
        Face& operator*() { return *it; }
    };
    Iterator_on_faces faces_begin() { return Iterator_on_faces(faces.begin()); }
    Iterator_on_faces faces_past_the_end() { return Iterator_on_faces(faces.end()); }

    struct Circulator_on_faces {
        std::vector<Face>::iterator it;
        explicit Circulator_on_faces() = default;
        explicit Circulator_on_faces(std::vector<Face>::iterator it_) : it(it_) {}
        Circulator_on_faces& operator++() { ++it; return *this; }
        Circulator_on_faces& operator--() { --it; return *this; }
        bool operator!=(const Circulator_on_faces& other) const { return it != other.it; }
        Face& operator*() { return *it; }
    };
    Circulator_on_faces incident_faces(Vertex v) { return Circulator_on_faces(faces.begin() + v.triangleId); }
    Circulator_on_faces incident_faces(int v) { return Circulator_on_faces(faces.begin() + vertices.at(v).triangleId); }

    struct Circulator_on_vertices {
        std::vector<Vertex>::iterator it;
        Circulator_on_vertices() = default;
        explicit Circulator_on_vertices(std::vector<Vertex>::iterator it_) : it(it_) {}
        Circulator_on_vertices& operator++() { ++it; return *this; }
        bool operator!=(const Circulator_on_vertices& other) const { return it != other.it; }
        Vertex& operator*() { return *it; }
    };
    Circulator_on_vertices incident_vertices(Face f) { return Circulator_on_vertices(vertices.begin() + f.vertices[0]); }
    Circulator_on_vertices incident_vertices(int f) { return Circulator_on_vertices(vertices.begin() + faces.at(f).vertices[0]); }

    Mesh::Iterator_on_faces itf;
    Mesh::Iterator_on_vertices itv;
    Mesh::Circulator_on_faces cf;
    Mesh::Circulator_on_vertices cv;

private:
    std::map<std::pair<int,int>,std::pair<int,int>> map;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

#endif // MESH_H