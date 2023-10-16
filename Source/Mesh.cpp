#include <iostream>
#include <fstream>
#include "Include/Mesh.h"
#include "Include/Utils.h"

Mesh::Mesh() {
    double width=0.5, depth=0.6, height=0.8;
    Point a(-0.5*width,-0.5*depth,-0.5*height);
    Point b(-0.5*width,0.5 *depth,-0.5*height);
    Point c(0.5*width ,-0.5*depth,-0.5*height);
    Point d(-0.5*width,-0.5*depth, 0.5*height);

    vertices.emplace_back(a, 0); // 0
    vertices.emplace_back(b, 1); // 1
    vertices.emplace_back(c, 2); // 2
    vertices.emplace_back(d, 3); // 3

    faces.emplace_back(0, 3, 2, 2, 3, 4);
    faces.emplace_back(0, 1, 3, 1, 3, 4);
    faces.emplace_back(2, 3, 1, 1, 2, 4);
    faces.emplace_back(2, 1, 0, 2, 3, 4);
}

Mesh::~Mesh() {
}

void Mesh::drawTriangle(int i, double r, double g, double b) {
    glColor3d(r,g,b);
    glBegin(GL_TRIANGLES);
    glPointDraw(vertices.at(faces[i].vertices[0]).point);
    glPointDraw(vertices.at(faces[i].vertices[1]).point);
    glPointDraw(vertices.at(faces[i].vertices[2]).point);
    glEnd();
}

void Mesh::drawMesh(DrawMode drawMode) {
    switch (drawMode) {
        case DRAW_MESH:
            drawMeshColor();
            break;
        case DRAW_MESH_ITERATOR:
            drawMeshIterator();
            break;
        case DRAW_MESH_CIRCULATOR:
            drawMeshCirculator();
            break;
        case DRAW_MESH_WIREFRAME:
            drawMeshWireFrame();
            break;
        default:
            drawMeshColor();
            break;
    }
}

void Mesh::drawMeshColor() {
    double r = 0.8; double g = 0.2; double b = 0.2;
    for(int i = 0; i < faces.size(); i++) {
        drawTriangle(i, r, g, b);
    }
}

void Mesh::drawMeshIterator() {
    double r = 0.3; double g = 1.0; double b = 0.3;
    glColor3d(r,g,b);
    glBegin(GL_TRIANGLES);
    glPointDraw(vertices.at(itf.it->vertices[0]).point);
    glPointDraw(vertices.at(itf.it->vertices[1]).point);
    glPointDraw(vertices.at(itf.it->vertices[2]).point);
    glEnd();

    r = 0.8; g = 0.2; b = 0.2;
    for(int i = 0; i < faces.size(); i++) {
        if(vertices.at(faces[i].vertices[0]).point != vertices.at(itf.it->vertices[0]).point ||
           vertices.at(faces[i].vertices[1]).point != vertices.at(itf.it->vertices[1]).point ||
           vertices.at(faces[i].vertices[2]).point != vertices.at(itf.it->vertices[2]).point)
        {
            r = 0.8; g = 0.2; b = 0.2;
            drawTriangle(i, r, g, b);
        }
    }
}

void Mesh::drawMeshCirculator() {
    double r = 0.3; double g = 0.3; double b = 1.0;
    glColor3d(r,g,b);
    glBegin(GL_TRIANGLES);
    glPointDraw(vertices.at(cf.it->vertices[0]).point);
    glPointDraw(vertices.at(cf.it->vertices[1]).point);
    glPointDraw(vertices.at(cf.it->vertices[2]).point);
    glEnd();

    r = 0.8; g = 0.2; b = 0.2;
    for(int i = 0; i < faces.size(); i++) {
        if(vertices.at(faces[i].vertices[0]).point != vertices.at(cf.it->vertices[0]).point ||
           vertices.at(faces[i].vertices[1]).point != vertices.at(cf.it->vertices[1]).point ||
           vertices.at(faces[i].vertices[2]).point != vertices.at(cf.it->vertices[2]).point)
        {
            r = 0.8; g = 0.2; b = 0.2;
            glColor3d(r,g,b);
            drawTriangle(i, r, g, b);
        }
    }
}

void Mesh::drawMeshWireFrame() {
    for(int i = 0; i < faces.size(); i++) {
        glColor3d(0.4,0.4,0.4);
        glBegin(GL_LINE_STRIP);
        glPointDraw(vertices.at(faces[i].vertices[0]).point);
        glPointDraw(vertices.at(faces[i].vertices[1]).point);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glPointDraw(vertices.at(faces[i].vertices[1]).point);
        glPointDraw(vertices.at(faces[i].vertices[2]).point);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glPointDraw(vertices.at(faces[i].vertices[0]).point);
        glPointDraw(vertices.at(faces[i].vertices[2]).point);
        glEnd();
    }
}

void Mesh::drawMeshStitching() {
    for(int i = 0; i < faces.size(); i++) {
        glColor3d(0.0,1.0,1.0);

        Point faceBarycenter = (vertices.at(faces[i].vertices[0]).point +
                                vertices.at(faces[i].vertices[1]).point +
                                vertices.at(faces[i].vertices[2]).point) / 3;

        Point firstNeighborBarycenter  = (vertices.at(faces.at(faces.at(i).adjacentTrianglesId[0]).vertices[0]).point +
                                          vertices.at(faces.at(faces.at(i).adjacentTrianglesId[0]).vertices[1]).point +
                                          vertices.at(faces.at(faces.at(i).adjacentTrianglesId[0]).vertices[2]).point) / 3;

        Point secondNeighborBarycenter = (vertices.at(faces.at(faces.at(i).adjacentTrianglesId[1]).vertices[0]).point +
                                          vertices.at(faces.at(faces.at(i).adjacentTrianglesId[1]).vertices[1]).point +
                                          vertices.at(faces.at(faces.at(i).adjacentTrianglesId[1]).vertices[2]).point) / 3;

        Point thirdNeighborBarycenter  = (vertices.at(faces.at(faces.at(i).adjacentTrianglesId[2]).vertices[0]).point +
                                          vertices.at(faces.at(faces.at(i).adjacentTrianglesId[2]).vertices[1]).point +
                                          vertices.at(faces.at(faces.at(i).adjacentTrianglesId[2]).vertices[2]).point) / 3;

        glBegin(GL_LINE_STRIP);
        glPointDraw(faceBarycenter);
        glPointDraw(firstNeighborBarycenter);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glPointDraw(faceBarycenter);
        glPointDraw(secondNeighborBarycenter);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glPointDraw(faceBarycenter);
        glPointDraw(thirdNeighborBarycenter);
        glEnd();
    }
}

void Mesh::drawInfPoint() {
    Point infPoint(0,0,-10);
    glColor3d(0.0,1.0,0.0);
    for (int i = 0; i < faces.size(); i++) {
        glBegin(GL_LINE_STRIP);
        if(faces.at(i).adjacentTrianglesId[0] == -1) {
            glPointDraw(vertices.at(faces.at(i).vertices[0]).point);
            glPointDraw(vertices.at(faces.at(i).vertices[1]).point);
            glPointDraw(infPoint);
        }
        if(faces.at(i).adjacentTrianglesId[1] == -1) {
            glPointDraw(vertices.at(faces.at(i).vertices[1]).point);
            glPointDraw(vertices.at(faces.at(i).vertices[2]).point);
            glPointDraw(infPoint);
        }
        if(faces.at(i).adjacentTrianglesId[2] == -1) {
            glPointDraw(vertices.at(faces.at(i).vertices[0]).point);
            glPointDraw(vertices.at(faces.at(i).vertices[2]).point);
            glPointDraw(infPoint);
        }
        glEnd();
    }
}

void Mesh::loadOFF(const char *filename, bool isTriangulated) {
    vertices.clear(); faces.clear();

    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    std::string line; file >> line;
    int numVertices, numFaces, numEdges;
    file >> numVertices >> numFaces >> numEdges;
    for(int i = 0; i < numVertices; i++) {
        double x, y, z;
        file >> x >> y >> z;
        vertices.emplace_back(Point(x, y, z), -1);
    }

    for(int i = 0; i < numFaces; i++) {

        int nbVerticesInFace; file >> nbVerticesInFace;
        int verticesInFace[nbVerticesInFace];

        for(int j = 0; j < nbVerticesInFace; j++) {
            file >> verticesInFace[j];
        }

        if(!isTriangulated) {
            int trash;
            for (int j = 0; j < 3; j++) {
                file >> trash;
            }
        }

        faces.emplace_back(verticesInFace[0], verticesInFace[1], verticesInFace[2], -1, -1, -1);

        std::pair<int,int> edge0 = edge(verticesInFace[0], verticesInFace[1]);
        std::pair<int,int> edge1 = edge(verticesInFace[1], verticesInFace[2]);
        std::pair<int,int> edge2 = edge(verticesInFace[0], verticesInFace[2]);

        insertMap(edge0, i, 2);
        insertMap(edge1, i, 0);
        insertMap(edge2, i, 1);
    }
    file.close();
}

void Mesh::initializeIteratorsAndCirulators() {
    itf = this->faces_begin();
    itv = this->vertices_begin();
    cf = this->incident_faces(*itv);
    cv = this->incident_vertices(*itf);
}

void Mesh::insertMap(std::pair<int,int> edge, int faceId, int sommetId) {
    if(map.find(edge) == map.end()) {
        std::pair<int,int> val = std::make_pair(faceId,sommetId);
        std::pair<std::pair<int,int>,std::pair<int,int>> entry(edge, val);
        map.insert(entry);
        vertices.at(edge.first).triangleId = faceId;
        vertices.at(edge.second).triangleId = faceId;
    }
    else {
        int oppositeFaceId = map.find(edge)->second.first;
        int oppositeSommetId = map.find(edge)->second.second;
        faces.at(oppositeFaceId).adjacentTrianglesId[oppositeSommetId] = faceId;
        faces.at(faceId).adjacentTrianglesId[sommetId] = oppositeFaceId;
    }
}

std::pair<int,int> Mesh::edge(int v1, int v2) {
    if(v1 < v2) { return std::make_pair(v1,v2); }
    return std::make_pair(v2,v1);
}

void Mesh::saveOFF(QString filename) {
    std::ofstream file;
    file.open(filename.toStdString().c_str());
    file << "OFF\n";
    file << vertices.size() << " " << faces.size() << " 0\n";
    for(int i = 0; i < vertices.size(); i++) {
        file << vertices.at(i).point._x << " " << vertices.at(i).point._y << " " << vertices.at(i).point._z << "\n";
    }
    for(int i = 0; i < faces.size(); i++) {
        file << "3 " << faces.at(i).vertices[0] << " " << faces.at(i).vertices[1] << " " << faces.at(i).vertices[2] << "\n";
    }
    file.close();
}

double Mesh::orientationTest(Point a, Point b, Point c) {
    return a._x*(b._y - c._y) + b._x*(c._y - a._y) + c._x*(a._y - c._y);
}

void Mesh::flipEdge(int face0, int face1) {
    Face f0 = faces.at(face0);
    Face f1 = faces.at(face1);

    int sharedPoint1, sharedPoint2, uniquePointF0, uniquePointF1;
    findCommonEdge(face0, face1, sharedPoint1, sharedPoint2, uniquePointF0, uniquePointF1);
    if (sharedPoint1 == -1 || sharedPoint2 == -1 || uniquePointF0 == -1 || uniquePointF1 == -1) {
        return;
    }

    int t1 = f0.adjacentTrianglesId[0];
    int t5 = f0.adjacentTrianglesId[1];
    int t4 = f0.adjacentTrianglesId[2];
    int t2 = f1.adjacentTrianglesId[0];
    int t0 = f1.adjacentTrianglesId[1];
    int t3 = f1.adjacentTrianglesId[2];

    faces.at(face0) = Face(sharedPoint1, uniquePointF1, uniquePointF0, t3, t4, t1);
    faces.at(face1) = Face(sharedPoint2, uniquePointF1, uniquePointF0, t2, t0, t5);

    vertices.at(sharedPoint1).triangleId = face0;
    vertices.at(sharedPoint2).triangleId = face1;
    vertices.at(uniquePointF0).triangleId = face0;
    vertices.at(uniquePointF1).triangleId = face1;
}

void Mesh::findCommonEdge(int face0, int face1, int &sharedPoint1, int &sharedPoint2, int &uniquePointF0, int &uniquePointF1) {
    Face f0 = faces.at(face0);
    Face f1 = faces.at(face1);

    sharedPoint1 = -1; sharedPoint2 = -1; uniquePointF0 = -1; uniquePointF1 = -1;

    for (int v0 : f0.vertices) {
        bool foundInF1 = false;
        for (int v1 : f1.vertices) {
            if (v0 == v1) {
                if (sharedPoint1 == -1) {
                    sharedPoint1 = v0;
                } else {
                    sharedPoint2 = v0;
                }
                foundInF1 = true;
                break;
            }
        }
        if (!foundInF1) {
            uniquePointF0 = v0;
        }
    }

    for (int v1 : f1.vertices) {
        if (v1 != sharedPoint1 && v1 != sharedPoint2) {
            uniquePointF1 = v1;
            break;
        }
    }
}

bool Mesh::inTriangle(int triId, Point p) {

    Point ab = vertices.at(faces.at(triId).vertices[1]).point - vertices.at(faces.at(triId).vertices[0]).point;
    Point bc = vertices.at(faces.at(triId).vertices[2]).point - vertices.at(faces.at(triId).vertices[1]).point;
    Point ca = vertices.at(faces.at(triId).vertices[0]).point - vertices.at(faces.at(triId).vertices[2]).point;

    Point ap = p - vertices.at(faces.at(triId).vertices[0]).point;
    Point bp = p - vertices.at(faces.at(triId).vertices[1]).point;
    Point cp = p - vertices.at(faces.at(triId).vertices[2]).point;

    double dotABAP = Math::Dot(ab, ap);
    double dotBCBP = Math::Dot(bc, bp);
    double dotCACP = Math::Dot(ca, cp);

    return (dotABAP >= 0 && dotBCBP >= 0 && dotCACP >=  0);
}

void Mesh::splitTriangle(int face, Point p) {
    if(!inTriangle(face, p)) {
        std::cout << "Point not in triangle" << std::endl;
        return;
    }

    int v1 = faces.at(face).vertices[0];
    int v2 = faces.at(face).vertices[1];
    int v3 = faces.at(face).vertices[2];

    int t1 = faces.at(face).adjacentTrianglesId[0];
    int t2 = faces.at(face).adjacentTrianglesId[1];
    int t3 = faces.at(face).adjacentTrianglesId[2];

    int v4 = vertices.size();
    vertices.emplace_back(p, -1);

    int t4 = faces.size();
    faces.emplace_back(v1, v2, v4, t1, t4, -1);
    faces.emplace_back(v2, v3, v4, t2, t4, -1);
    faces.emplace_back(v3, v1, v4, t3, t4, -1);

    vertices.at(v1).triangleId = t4;
    vertices.at(v2).triangleId = t4;
    vertices.at(v3).triangleId = t4;

}
