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

void Mesh::drawMesh() {
    for(int i = 0; i < faces.size(); i++) {
        glColor3d(0.4,0.4,0.4);
        glBegin(GL_TRIANGLES);
        glPointDraw(vertices.at(faces[i].vertices[0]).point);
        glPointDraw(vertices.at(faces[i].vertices[1]).point);
        glPointDraw(vertices.at(faces[i].vertices[2]).point);
        glEnd();
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
            for (int j = 0; j < 3; j++) {
                int trash;
                file >> trash;
            }
        }

        faces.emplace_back(verticesInFace[0], verticesInFace[1], verticesInFace[2], -1, -1, -1);

        std::pair<int,int> edge0 = edge(verticesInFace[0], verticesInFace[1]);
        std::pair<int,int> edge1 = edge(verticesInFace[1], verticesInFace[2]);
        std::pair<int,int> edge2 = edge(verticesInFace[0], verticesInFace[2]);

        // Si je ne trouve pas, j'insère
        if(map.find(edge0) == map.end()) {
            std::pair<int,int> val = std::make_pair(i,2);
            std::pair<std::pair<int,int>,std::pair<int,int>> entry(edge0, val);
            map.insert(entry);
            vertices.at(edge0.first).triangleId = i;
            vertices.at(edge0.second).triangleId = i;
        }
        // Sinon ça veut dire que j'ai déjà vu cette arrête dans l'autre sens
        else {
            int oppositeFaceId = map.find(edge0)->second.first;
            int sommetId = map.find(edge0)->second.second;
            faces.at(oppositeFaceId).adjacentTrianglesId[sommetId] = i;
            faces.at(i).adjacentTrianglesId[2] = oppositeFaceId;
        }

        if(map.find(edge1) == map.end()) {
            std::pair<int,int> val = std::make_pair(i,0);
            std::pair<std::pair<int,int>,std::pair<int,int>> entry(edge1, val);
            map.insert(entry);
            vertices.at(edge1.first).triangleId = i;
            vertices.at(edge1.second).triangleId = i;
        }
        else {
            int oppositeFaceId = map.find(edge1)->second.first;
            int sommetId = map.find(edge1)->second.second;
            faces.at(oppositeFaceId).adjacentTrianglesId[sommetId] = i;
            faces.at(i).adjacentTrianglesId[0] = oppositeFaceId;
        }

        if(map.find(edge2) == map.end()) {
            std::pair<int,int> val = std::make_pair(i,1);
            std::pair<std::pair<int,int>,std::pair<int,int>> entry(edge2, val);
            map.insert(entry);
            vertices.at(edge2.first).triangleId = i;
            vertices.at(edge2.second).triangleId = i;
        }
        else {
            int oppositeFaceId = map.find(edge2)->second.first;
            int sommetId = map.find(edge2)->second.second;
            faces.at(oppositeFaceId).adjacentTrianglesId[sommetId] = i;
            faces.at(i).adjacentTrianglesId[1] = oppositeFaceId;
        }
    }

    file.close();
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

Mesh::~Mesh() {
}
