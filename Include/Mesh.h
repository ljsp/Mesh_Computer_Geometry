#ifndef MESH_H
#define MESH_H

#include <QOpenGLWidget>
#include "Utils.h"
#include "Structures.h"

class Mesh
{
public:
    std::map<std::pair<int,int>,std::pair<int,int>> map;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

public:
    Mesh();
    ~Mesh();

    void box2D();

    void drawTriangle(int i, double r, double g, double b);
    void drawMesh(DrawMode drawMode);
    void drawMeshColor();
    void drawMeshIterator();
    void drawMeshCirculator();
    void drawMeshWireFrame();
    void drawMeshStitching();
    void drawMeshLaplacian();
    void drawMeshNormals();
    void drawInfPoint();

    void initializeIteratorsAndCirulators();
    void loadOFF(const char* filename);
    void loadPoints(const char* filename);
    void saveOFF(QString filename);
    void insertMap(std::pair<int,int> edge, int faceId, int sommetId);
    static std::pair<int,int> edge(int v1, int v2);

    void computeNormals();

    double calculateAreaFacei(Vertex v);
    Point laplacianOfVertex(int idVertex);
    std::vector<int> firstRing(int idVertex);
    void computeLaplacian();

    int positionGlobalInVertices(Vertex & v);
    void flipEdge(int face0, int face1);
    void splitTriangle(int face, Point p);
    int indexFacePointInside(Point P);
    int foundFace(int a, int b);

    int whichIndex(int indiceFaceCurrent,int indiceVertexArround);
    bool isEdgeDelaunay(int vertexA, int vertexB);
    void findNonDelaunayEdge();
    bool isDelaunayConditionSatisfied(int vertexA, int vertexB, int vertexC, int faceIndex);
    Point calculateCircumcenter(const Point& A, const Point& B, const Point& C);
    bool estDansCercleCirconscrit(const Point& A, const Point& B, const Point& C, const Point& point);

    void simplifyMesh(int nbFace);
    void splitEdge(int face, int edge);
    void contractEdge(int face, int edge);

    struct Iterator_on_faces
    {
        Mesh* mesh = nullptr;
        int id = 0;

        Iterator_on_faces() = default;
        explicit Iterator_on_faces(Mesh* m, int i): mesh(m), id(i) {}
        bool hasNext() { return id < mesh->faces.size() - 1; }
        int indice() const { return id; }
        Face& operator*() { return mesh->faces.at(id); }
        Face* operator->() { return &mesh->faces.at(id); }
        Iterator_on_faces& operator++() {
            if(this->hasNext()) id++;
            return *this;
        }
        Iterator_on_faces& operator--() {
            if(this->id > 0) id--;
            return *this;
        }
    };

    struct Iterator_on_vertices
    {
        Mesh *mesh = nullptr;
        int id = 0;

        Iterator_on_vertices() = default;
        explicit Iterator_on_vertices(Mesh* m, int i): mesh(m), id(i) {}
        bool hasNext() { return id < mesh->vertices.size() - 1; }
        int indice() const { return id; }
        Vertex& operator*() { return mesh->vertices.at(id); }
        Vertex* operator->() { return &mesh->vertices.at(id); }
        Iterator_on_vertices& operator++() {
            if(this->hasNext()) this->id++;
            return *this;
        }
        Iterator_on_vertices& operator--() {
            if(this->id > 0) this->id--;
            return *this;
        }
    };

    Iterator_on_vertices vertices_begin()        { return Iterator_on_vertices(this, 0); }
    Iterator_on_vertices vertices_past_the_end() { return Iterator_on_vertices(this, vertices.size()); }
    Iterator_on_faces    faces_begin()           { return Iterator_on_faces(   this, 0); }
    Iterator_on_faces    faces_past_the_end()    { return Iterator_on_faces(   this, faces.size()); }

    struct Circulator_on_faces
    {
        Mesh* mesh;
        int idFace, idPivot; // idPivot est le sommet autour duquel on tourne

        Circulator_on_faces() = default;
        explicit Circulator_on_faces(Mesh* m, Vertex &_v) : mesh(m), idFace(_v.triangleId){
            idPivot = mesh->positionGlobalInVertices(_v);
            if(idFace == -1) {
                for (int i = 0; i < m->faces.size(); i++) {
                    if (!m->faces[i].isVisible) {
                        idFace = i;
                        break;
                    }
                }
            }
        }

        /*
        explicit Circulator_on_faces(Mesh* m, Vertex& v) : mesh(m){
            idPivot = mesh->positionGlobalInVertices(v);
            if(idPivot != 0){
                idFace = mesh->vertices[idPivot].triangleId;
            }else{
                for(int i = 0; i<m->faces.size();i++){
                    if(!m->faces[i].isVisible){
                        idFace = i;
                        break;
                    }
                }
                idFace = -1;
            }
        }*/


        Circulator_on_faces(const Circulator_on_faces& c) = default;
        Circulator_on_faces(Circulator_on_faces&& c) = default;

        int indice( ){ return idFace; }

        Face* operator->(){ return &mesh->faces[idFace]; }

        int operator*(){ return mesh->faces[idFace].vertices[idPivot]; }

        /*Circulator_on_faces& operator++(){
            Face f = mesh->faces[idFace];
            for(int i = 0; i < 3; i++) {
                if(f.vertices[i] == idPivot)
                    this->idFace = f.adjacentTrianglesId[(i+1)%3]; // Trouver la face adjacente
            }
            return *this;
        }*/

        Circulator_on_faces operator++(){
            int indexLocalVertex = mesh->whichIndex(idFace,idPivot);
            idFace = mesh->faces[idFace].adjacentTrianglesId[(indexLocalVertex + 2)%3];
            return (*this);
        }

        /*Circulator_on_faces& operator--(){
            Face f = mesh->faces[idFace];
            for(int i = 0; i < 3; i++) {
                if(f.vertices[i] == idPivot)
                    this->idFace = f.adjacentTrianglesId[(i+2)%3]; // Trouver la face adjacente
            }
            return *this;
        }*/

        Circulator_on_faces operator--(){
            int indexLocalVertex = mesh->whichIndex(idFace,idPivot);
            idFace = mesh->faces[idFace].adjacentTrianglesId[(indexLocalVertex + 1)%3];
            return (*this);
        }

        Circulator_on_faces & operator=(const Circulator_on_faces& c) = default;
        Circulator_on_faces & operator=(Circulator_on_faces&& c) = default;
    };

    struct Circulator_on_vertices
    {
        Mesh* mesh;
        int idFace, idPivot, idSuivant;
        bool isValid;

        Circulator_on_vertices() = default;
        explicit Circulator_on_vertices(Mesh* _mesh,  Vertex &_v) : mesh(_mesh), idFace(_v.triangleId){
            Face &f = _mesh->faces[idFace];
            isValid = true;
            for(int i = 0; i < 3; i++){
                if(mesh->vertices.at(f.vertices[i]).point == _v.point){
                    idPivot = f.vertices[i];
                    idSuivant = f.vertices[(i+1)%3];
                }
            }
        }

        int indice(){ return idSuivant; }

        Vertex* operator->(){ return &mesh->vertices[idSuivant]; }

        Circulator_on_vertices operator++(int) {
            Face f = mesh->faces[idFace];
            for(int i = 0; i < 3; i++) {
                if(f.vertices[i] == idSuivant) {
                    if(f.adjacentTrianglesId[i] == -1) {
                        isValid = false;
                    } else {
                        this->idFace = f.adjacentTrianglesId[i];
                    }
                }
            }

            f = mesh->faces[this->idFace];
            for(int i = 0; i < 3; i++) {
                if(f.vertices[i] == idPivot) {
                    this->idSuivant = f.vertices[(i+1)%3];
                }
            }
            return *this;
        }

        Circulator_on_vertices operator--(int){
            Face f = mesh->faces[idFace];
            for(int i = 0; i < 3; i++) {
                if(f.vertices[i] == idSuivant)
                    this->idFace = f.adjacentTrianglesId[i];
            }
            f = mesh->faces[this->idFace];
            for(int i = 0; i < 3; i++) {
                if(f.vertices[i] == idPivot)
                    this->idSuivant = f.vertices[(i+2)%3];
            }
            return *this;
        }
    };

    Circulator_on_faces incident_faces(Vertex v) { return Circulator_on_faces(this, v); }
    Circulator_on_faces incident_faces(int v) { return Circulator_on_faces(this, vertices.at(v)); }
    Circulator_on_vertices incident_vertices(Vertex v) { return Circulator_on_vertices(this, v); }
    Circulator_on_vertices incident_vertices(int v) { return Circulator_on_vertices(this, vertices.at(v)); }

    Mesh::Iterator_on_faces itf;
    Mesh::Iterator_on_vertices itv;
    Circulator_on_faces cf;
    Circulator_on_vertices cv;
};

#endif // MESH_H