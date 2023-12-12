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

void Mesh::box2D(){
    vertices.clear();
    Vertex infinitePoint = Vertex(Point(0,0,-50),-1);
    vertices.push_back(infinitePoint); //point infinie du 2D

    vertices.push_back(Vertex(Point(0,0,0),0));
    vertices.push_back(Vertex(Point(1,0,0),0));
    vertices.push_back(Vertex(Point(1,1,0),0));
    vertices.push_back(Vertex(Point(0,1,0),1));

    faces.clear();
    faces.push_back(Face(1,2,3,-1,1,-1));
    faces.push_back(Face(1,3,4,-1,-1,0));

    //infinite
    faces.push_back(Face(1,0,2,3,0,5,false));
    faces.push_back(Face(2,0,3,4,0,2,false));
    faces.push_back(Face(3,0,4,5,1,3,false));
    faces.push_back(Face(4,0,1,2,1,4,false));
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
            drawMeshNormals();
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
        case DRAW_MESH_LAPLACIAN:
            drawMeshLaplacian();
            break;
        case DRAW_MESH_NORMALS:
            drawMeshNormals();
            break;
        default:
            drawMeshColor();
            break;
    }
}

void Mesh::drawMeshColor() {
    double r = 0.8; double g = 0.2; double b = 0.2;
    for(int i = 0; i < faces.size(); i++) {
        if(faces.at(i).isVisible) {
            drawTriangle(i, r, g, b);
        }
    }
}

void Mesh::drawMeshIterator() {
    double r = 0.3; double g = 1.0; double b = 0.3;

    glColor3d(r,g,b);
    glBegin(GL_TRIANGLES);
    glPointDraw(vertices.at(itf->vertices[0]).point);
    glPointDraw(vertices.at(itf->vertices[1]).point);
    glPointDraw(vertices.at(itf->vertices[2]).point);
    glEnd();

    r = 0.8; g = 0.2; b = 0.2;
    for(int i = 0; i < faces.size(); i++) {
        if(vertices.at(faces[i].vertices[0]).point != vertices.at(itf->vertices[0]).point ||
           vertices.at(faces[i].vertices[1]).point != vertices.at(itf->vertices[1]).point ||
           vertices.at(faces[i].vertices[2]).point != vertices.at(itf->vertices[2]).point)
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
    glPointDraw(vertices.at(cf->vertices[0]).point);
    glPointDraw(vertices.at(cf->vertices[1]).point);
    glPointDraw(vertices.at(cf->vertices[2]).point);
    glEnd();

    r = 0.8; g = 0.2; b = 0.2;
    for(int i = 0; i < faces.size(); i++) {
        if(vertices.at(faces[i].vertices[0]).point != vertices.at(cf->vertices[0]).point ||
           vertices.at(faces[i].vertices[1]).point != vertices.at(cf->vertices[1]).point ||
           vertices.at(faces[i].vertices[2]).point != vertices.at(cf->vertices[2]).point)
        {
            r = 0.8; g = 0.2; b = 0.2;
            glColor3d(r,g,b);
            drawTriangle(i, r, g, b);
        }
    }
}

void Mesh::drawMeshWireFrame() {
    for(int i = 0; i < faces.size(); i++) {
        glColor3d(faces.at(i).normal._x,
                  faces.at(i).normal._y,
                  faces.at(i).normal._z);
        if(faces.at(i).isVisible) {
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
}

void Mesh::drawMeshNormals() {
    for(int i = 0; i < faces.size(); i++) {
        if(faces.at(i).isVisible) {
            glColor3d(faces.at(i).normal._x,
                      faces.at(i).normal._y,
                      faces.at(i).normal._z);
            glBegin(GL_TRIANGLES);
            glPointDraw(vertices.at(faces[i].vertices[0]).point);
            glPointDraw(vertices.at(faces[i].vertices[1]).point);
            glPointDraw(vertices.at(faces[i].vertices[2]).point);
            glEnd();
        }
    }
}

void Mesh::drawMeshStitching() {
    for(int i = 0; i < faces.size(); i++) {
        if(faces.at(i).isVisible) {
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
}

void Mesh::drawInfPoint() {
    Point infPoint(0,0,-10);
    glColor3d(0.0,1.0,0.0);
    for (int i = 0; i < faces.size(); i++) {
        if(!faces.at(i).isVisible) {
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
}

void Mesh::drawMeshLaplacian() {
    for (int i = 0; i < faces.size(); ++i) {
        if(faces.at(i).isVisible) {
            glBegin(GL_TRIANGLES);
            for(int j = 0; j < 3; j++){
                int id = faces[i].vertices[j];
                double val = Math::Norm(vertices[id].laplacian);
                std::array<float, 3> rgb = HSV(val);
                glColor3f(rgb[0], rgb[1], rgb[2]);
                glPointDraw(vertices[id].point);
            }
            glEnd();
        }
    }
}

void Mesh::initializeIteratorsAndCirulators() {
    itf = faces_begin();
    itv = vertices_begin();
    cf = incident_faces(*itv);
    cv = incident_vertices(*itv);
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

void Mesh::loadPoints(const char *filename) {
    vertices.clear(); faces.clear();

    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    int numVertices;
    file >> numVertices;
    for(int i = 0; i < numVertices; i++) {
        double x, y, z;
        file >> x >> y >> z;
        vertices.emplace_back(Point(x / 100, y / 100, z / 100), -1);
    }

    for(int i = 0; i < numVertices - 1; i+=3) {
        faces.emplace_back(i, i+1, i+2, -1, -1, -1);
        std::pair<int,int> edge0 = edge(i, i+1);
        std::pair<int,int> edge1 = edge(i+1, i+2);
        std::pair<int,int> edge2 = edge(i, i+2);

        insertMap(edge0, i/3, 2);
        insertMap(edge1, i/3, 0);
        insertMap(edge2, i/3, 1);
    }

    file.close();
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

void Mesh::computeNormals() {
    for(int i = 0; i < faces.size(); i++) {
        Point a = vertices.at(faces.at(i).vertices[0]).point;
        Point b = vertices.at(faces.at(i).vertices[1]).point;
        Point c = vertices.at(faces.at(i).vertices[2]).point;
        Point normal = Math::Cross(b-a, c-a);
        normal = Math::Normalize(normal);
        faces.at(i).normal = normal;
        //printf("Face %d : %f %f %f\n", i, normal._x, normal._y, normal._z);
    }
}

double Mesh::calculateAreaFacei(Vertex v){
    Circulator_on_faces cf = incident_faces(v);
    Circulator_on_faces cfbegin = cf;
    double area = 0;
    do {
        Face f = faces[cf.indice()];
        Point p1 = vertices[f.vertices[0]].point;
        Point p2 = vertices[f.vertices[1]].point;
        Point p3 = vertices[f.vertices[2]].point;
        area += triangleArea(p1, p2, p3);
        ++cf;
    } while(cf.indice() != cfbegin.indice());
    return area / 3.0;
}

std::vector<int> Mesh::firstRing(int idVertex) {
    std::vector<int> firstRing;
    Circulator_on_vertices cv = incident_vertices(vertices.at(idVertex));
    Circulator_on_vertices cvBegin = cv;
    do {
        firstRing.push_back(cv.indice());
        cv++;
    } while(cv.indice() != cvBegin.indice());
    return firstRing;
}

Point Mesh::laplacianOfVertex(int vertexId) {

    Vertex vertex_i = vertices.at(vertexId);

    Point laplacian = Point(0,0,0);

    std::vector<int> firstRing = this->firstRing(vertexId);
    int neighbours = firstRing.size();

    for (int i = 0; i < neighbours; ++i) {

        int id_j = firstRing[i];
        int id_j_next = firstRing[(i + 1) % neighbours];
        int id_j_prev = firstRing[(i - 1 + neighbours) % neighbours];

        Vertex vertex_j = vertices.at(id_j);
        Vertex vertex_j_next = vertices.at(id_j_next);
        Vertex vertex_j_prev = vertices.at(id_j_prev);

        Point v1 = vertex_i.point - vertex_j_prev.point;
        Point v2 = vertex_j.point - vertex_j_prev.point;
        Point v3 = vertex_i.point - vertex_j_next.point;
        Point v4 = vertex_j.point - vertex_j_next.point;

        double cotAlpha = cotan(v1, v2);
        double cotBeta = cotan(v3, v4);

        laplacian._x += (cotAlpha + cotBeta) * (vertex_i.point._x - vertex_j.point._x);
        laplacian._y += (cotAlpha + cotBeta) * (vertex_i.point._y - vertex_j.point._y);
        laplacian._z += (cotAlpha + cotBeta) * (vertex_i.point._z - vertex_j.point._z);
    }

    double Ai = calculateAreaFacei(vertex_i);

    laplacian._x = 1/(2*Ai) * laplacian._x;
    laplacian._y = 1/(2*Ai) * laplacian._y;
    laplacian._z = 1/(2*Ai) * laplacian._z;

    return laplacian;
}

void Mesh::computeLaplacian() {
    for (int i = 0; i < vertices.size(); ++i) {
        Point val = laplacianOfVertex(i);
        vertices[i].laplacian = val;
        //printf("Laplacian of vertex %d : (%f, %f, %f)\n", i, val._x, val._y, val._z);
    }
}

int Mesh::foundFace(int a, int b) {
    for (int i = 0; i < faces.size(); i++) {
        if(faces[i].isVisible){
            int vertices[3] = {faces[i].vertices[0], faces[i].vertices[1], faces[i].vertices[2]};
            // Vérifiez si les sommets a et b appartiennent à ce triangle
            if ((a == vertices[0] || a == vertices[1] || a == vertices[2]) &&
                (b == vertices[0] || b == vertices[1] || b == vertices[2])) {
                return i; // Retourne l'indice de la face
            }
        }
    }
    return -1; // Aucune face trouvée
}


int Mesh::positionGlobalInVertices(Vertex & v){
    int index = -1;
    for(int i = 0; i<vertices.size();i++){
        if(vertices[i].point == v.point){
            index = i;
            break;
        }
    }
    return index;
}

void Mesh::flipEdge(int a, int b) {
    int AoppB = -1;
    int BoppA = -1;
    for(int i = 0; i< 3; i++){
        if(faces[a].adjacentTrianglesId[i] == b){
            AoppB = i;
            break;
        }
    }

    for(int i = 0; i< 3; i++){
        if(faces[b].adjacentTrianglesId[i] == a){
            BoppA = i;
            break;
        }
    }

    //Store zone

    faces[a].vertices[(AoppB+2)%3] = faces[b].vertices[BoppA];
    faces[b].vertices[(BoppA+2)%3] = faces[a].vertices[AoppB];


    //modifier les adjacence
    faces[a].adjacentTrianglesId[AoppB] = faces[b].adjacentTrianglesId[(BoppA+1)%3];
    faces[b].adjacentTrianglesId[BoppA] = faces[a].adjacentTrianglesId[(AoppB+1)%3];

    faces[a].adjacentTrianglesId[(AoppB+1)%3] = b;
    faces[b].adjacentTrianglesId[(BoppA+1)%3] = a;

    int opposeHorsB = -1, opposeHorsA =-1;
    for(int i = 0; i< 3; i++){
        if(faces[b].adjacentTrianglesId[BoppA] != -1){
            if(faces[faces[b].adjacentTrianglesId[BoppA]].adjacentTrianglesId[i] == a){
                opposeHorsB = i;
                break;
            }
        }
    }

    for(int i = 0; i< 3; i++){
        if(faces[a].adjacentTrianglesId[AoppB] != -1){
            if(faces[faces[a].adjacentTrianglesId[AoppB]].adjacentTrianglesId[i] == b){
                opposeHorsA = i;
                break;
            }
        }
    }

    if(opposeHorsB!=-1)
        faces[faces[b].adjacentTrianglesId[BoppA]].adjacentTrianglesId[opposeHorsB] = b;
    if(opposeHorsA!=-1)
        faces[faces[a].adjacentTrianglesId[AoppB]].adjacentTrianglesId[opposeHorsA] = a;

}

int Mesh::indexFacePointInside(Point P){
    for (int i = 0; i < faces.size(); i++) {
        if(faces[i].isVisible){
            const Point& A = vertices[faces[i].vertices[0]].point;
            const Point& B = vertices[faces[i].vertices[1]].point;
            const Point& C = vertices[faces[i].vertices[2]].point;

            int result = pointPosition(A, B, C, P);
            if (result == 1) {
                return i; // Le point est à l'intérieur de la face.
            }
        }
    }
    return -1; // Aucune face ne contient le point.
}

void Mesh::splitTriangle(int face, Point p) {
    int indFace = indexFacePointInside(p);
    vertices.push_back(Vertex(p,indFace)); //avant ou pendant le if ??
    int idNewVertice = vertices.size()-1;
    if(indFace == -1){
        std::cout << "insert infinite face point : " << p._x << "  " << p._y << std::endl;
        Circulator_on_faces cicFace1 = incident_faces(vertices[0]);
        Point a = vertices[faces[cicFace1.idFace].vertices[0]].point;
        Point c = vertices[faces[cicFace1.idFace].vertices[2]].point;
        while(Orientation(a,p, c) == 1) {
            ++cicFace1;     //ne pas commencer a circuler sur une arrete qui dois devenir un nouveau triangle
                            //car celle d'avant peut aussi en etre une mais notre bool sera sur false;
            a = vertices[faces[cicFace1.idFace].vertices[0]].point;
            c = vertices[faces[cicFace1.idFace].vertices[2]].point;
        }
        Circulator_on_faces cicFace2 = cicFace1;
        Circulator_on_faces cicFace0 = cicFace1;
        --cicFace0;
        Circulator_on_faces cicBegin = cicFace1;

        bool previousWasCreated = false;
        do{

            ++cicFace2;
            std::cout << "passage boucle circ infinite add point  " <<cicFace1.idFace << std::endl;
            int idCurrentFace = cicFace1.idFace;
            int indV1 = faces[idCurrentFace].vertices[0];
            int indV2 = faces[idCurrentFace].vertices[2];
            if(Orientation(vertices[indV1].point , p,  vertices[indV2].point) == 1){
                int indFaceAdja = foundFace(indV1,indV2);
                int indV3 =-1;
                for(int j=0; j<3; j++){
                    if(faces[indFaceAdja].vertices[j] == indV1 || faces[indFaceAdja].vertices[j] == indV2){
                        continue;
                    }else{
                        indV3 = j;
                        break;
                    }
                }
                if(indV3 == -1){
                    std::cout << "insert infinite face fail" << std::endl;
                }

                if(previousWasCreated){
                    --cicFace2;
                    int idNewFace = cicFace0.idFace;
                    faces[idCurrentFace].adjacentTrianglesId[0] = cicFace2.idFace;
                    faces[idCurrentFace].adjacentTrianglesId[1] = idNewFace;
                    --cicFace0;
                    faces[idCurrentFace].adjacentTrianglesId[2] = cicFace0.idFace;
                    faces[cicFace0.idFace].adjacentTrianglesId[0] = idCurrentFace;

                    faces[idNewFace].vertices[0] = indV1;
                    faces[idNewFace].vertices[1] = idNewVertice;
                    faces[idNewFace].vertices[2] = indV2;

                    faces[idNewFace].adjacentTrianglesId[0] = -1;
                    faces[idNewFace].adjacentTrianglesId[1] = indFaceAdja;
                    faces[idNewFace].adjacentTrianglesId[2] = -1; //fusioner avec ligne plus bas
                    faces[idNewFace].isVisible = true;


                    faces[idCurrentFace].vertices[0] = idNewVertice;

                    faces[idNewFace].adjacentTrianglesId[2] = idNewFace-1;//set vertice 2 adjacent sur face precedente.    //elle
                    faces[idNewFace-1].adjacentTrianglesId[0] = idNewFace;//set vertice 0 face precedente sur nous.
                    ++cicFace2;
                }else {
                    faces.push_back(Face(indV1,idNewVertice,indV2,-1,indFaceAdja,-1));
                    int idNewFace = faces.size()-1;

                    faces[indFaceAdja].adjacentTrianglesId[indV3] = idNewFace;  //modifie face adjacent du triangle contre le notre.

                    faces[idCurrentFace].adjacentTrianglesId[0] = idNewFace+1;
                    faces[idCurrentFace].adjacentTrianglesId[1] = idNewFace;

                    faces[idCurrentFace].vertices[2] = idNewVertice;

                    faces.push_back(Face(idNewVertice,0,indV2,cicFace2.idFace,idNewFace, idCurrentFace,false));
                    faces[cicFace2.idFace].adjacentTrianglesId[2] = idNewFace+1;

                    ++cicFace1;
                    ++cicFace0;
                    ++cicFace2;
                }

                previousWasCreated = true;
                //saute l'arrete convexe contenant le point a add


            }
            ++cicFace1;
            ++cicFace0;
        }while(cicFace1.idFace != cicBegin.idFace);
    }else{
        int indA = faces[indFace].vertices[0];
        int indB = faces[indFace].vertices[1];
        int indC = faces[indFace].vertices[2];
        int indP =  vertices.size() - 1;
        int indTriangleDroite = faces.size();
        int indTriangleGauche = faces.size() + 1;
        int exIndAdjacentA = faces[indFace].adjacentTrianglesId[0];
        int exIndAdjacentB = faces[indFace].adjacentTrianglesId[1];

        faces[indFace].adjacentTrianglesId[0] = indTriangleDroite;
        faces[indFace].adjacentTrianglesId[1] = indTriangleGauche;
        faces[indFace].vertices[2] = indP;

        faces.push_back(Face(indB,indC,indP));
        faces[indTriangleDroite].adjacentTrianglesId[0] = indTriangleGauche;
        faces[indTriangleDroite].adjacentTrianglesId[1] = indFace;
        faces[indTriangleDroite].adjacentTrianglesId[2] = exIndAdjacentA;

        faces.push_back(Face(indC,indA,indP));
        faces[indTriangleGauche].adjacentTrianglesId[0] = indFace;
        faces[indTriangleGauche].adjacentTrianglesId[1] = indTriangleDroite;
        faces[indTriangleGauche].adjacentTrianglesId[2] = exIndAdjacentB;

        for(int i =0; i<3; i++){
            if(faces[indTriangleDroite].adjacentTrianglesId[2] != -1){
                if(faces[faces[indTriangleDroite].adjacentTrianglesId[2]].adjacentTrianglesId[i] == indFace){
                    faces[faces[indTriangleDroite].adjacentTrianglesId[2]].adjacentTrianglesId[i] = indTriangleDroite;
                }
            }

            if(faces[indTriangleGauche].adjacentTrianglesId[2] != -1){
                if(faces[faces[indTriangleGauche].adjacentTrianglesId[2]].adjacentTrianglesId[i] == indFace){
                    faces[faces[indTriangleGauche].adjacentTrianglesId[2]].adjacentTrianglesId[i] = indTriangleGauche;
                }
            }
        }
    }

}

int Mesh::whichIndex(int indiceFaceCurrent,int indiceVertexArround ){
    int index = -1;
    for(int i = 0; i<3;i++){
        if(faces[indiceFaceCurrent].vertices[i] == indiceVertexArround){
            index = i;
            break;
        }
    }
    return index;
}

void Mesh::findNonDelaunayEdge() {
    for (int i = 1; i < vertices.size(); ++i) {

        Vertex vi = vertices.at(i);
        Circulator_on_vertices cv = incident_vertices(vi);
        Circulator_on_vertices cvBegin = cv;

        do {
            int indiceLocalI = whichIndex(cv.idFace, i);
            int j = faces[cv.idFace].vertices[(indiceLocalI + 1) %3];
            if (j != -1) {
                if (!isEdgeDelaunay(i, j)) {
                    std::cout << "Edge (" << i << ", " << j << ") is non-Delaunay." << std::endl;
                    flipEdge(i,j);
                }
            }
            cv++;
        } while (cv.indice() != cvBegin.indice() && cv.isValid);
    }
}

bool Mesh::isEdgeDelaunay(int vertexA, int vertexB) {
    // Trouver les faces partageant les sommets A et B
    std::vector<int> facesSharingVertexA;
    std::vector<int> facesSharingVertexB;

    for (int i = 0; i < faces.size(); ++i) {
        if (faces[i].containsVertex(vertexA)) {
            facesSharingVertexA.push_back(i);
        }
        if (faces[i].containsVertex(vertexB)) {
            facesSharingVertexB.push_back(i);
        }
    }

    // Trouver les faces communes
    std::vector<int> commonFaces;
    for (int i : facesSharingVertexA) {
        for (int j : facesSharingVertexB) {
            if (i == j) {
                commonFaces.push_back(i);
            }
        }
    }

    // Vérifier la condition de Delaunay pour les faces communes
    for (int faceIndex : commonFaces) {
        int thirdVertex = faces[faceIndex].getThirdVertex(vertexA, vertexB);
        if (!isDelaunayConditionSatisfied(vertexA, vertexB, thirdVertex, faceIndex)) {
            return false;
        }
    }

    return true;
}

bool Mesh::isDelaunayConditionSatisfied(int vertexA, int vertexB, int vertexC, int faceIndex) {
    const Point& A = vertices[vertexA].point;
    const Point& B = vertices[vertexB].point;
    const Point& C = vertices[vertexC].point;

    Point circumcenter = calculateCircumcenter(A, B, C);

    if (estDansCercleCirconscrit(A, B, C, circumcenter)) {
        return false;
    }

    return true;
}

Point Mesh::calculateCircumcenter(const Point& A, const Point& B, const Point& C) {
    // Calculer le milieu des côtés du triangle
    Point midAB((A._x + B._x) / 2.0, (A._y + B._y) / 2.0, (A._z + B._z) / 2.0);
    Point midBC((B._x + C._x) / 2.0, (B._y + C._y) / 2.0, (B._z + C._z) / 2.0);

    // Calculer les pentes perpendiculaires
    double slopeAB = -1.0 / ((B._y - A._y) / (B._x - A._x));
    double slopeBC = -1.0 / ((C._y - B._y) / (C._x - B._x));

    // Calculer les coordonnées du circumcenter
    double circumcenterX = (slopeAB * midAB._x - slopeBC * midBC._x + midBC._y - midAB._y) / (slopeAB - slopeBC);
    double circumcenterY = slopeAB * (circumcenterX - midAB._x) + midAB._y;

    return Point(circumcenterX, circumcenterY, 0.0);
}

bool Mesh::estDansCercleCirconscrit(const Point& A, const Point& B, const Point& C, const Point& point) {
    // Vérifier si le point est à l'intérieur du cercle circonscrit
    double dA = (A._x - point._x) * (A._x - point._x) + (A._y - point._y) * (A._y - point._y);
    double dB = (B._x - point._x) * (B._x - point._x) + (B._y - point._y) * (B._y - point._y);
    double dC = (C._x - point._x) * (C._x - point._x) + (C._y - point._y) * (C._y - point._y);

    double determinant = A._x * (B._y - C._y) - B._x * (A._y - C._y) + C._x * (A._y - B._y);

    return determinant * (dA * dB * dC) < 0.0;
}

void Mesh::splitEdge(int face, int edge) {
    int indA = faces[face].vertices[edge];
    int indB = faces[face].vertices[(edge+1)%3];
    Point p = (vertices[indA].point + vertices[indB].point) / 2;
    splitTriangle(face, p);
}

void Mesh::contractEdge(int face, int edge) {
    int indA = faces[face].vertices[edge];
    int indB = faces[face].vertices[(edge+1)%3];
    Point p = (vertices[indA].point + vertices[indB].point) / 2;
    vertices[indA].point = p;
    vertices[indB].point = p;
}

void Mesh::simplifyMesh(int nbFace) {
    while(faces.size() > nbFace) {
        int min = 1000000;
        int indice = -1;
        for(int i = 0; i < faces.size(); i++) {
            if(faces.at(i).isVisible) {
                int nbAdj = 0;
                for(int j = 0; j < 3; j++) {
                    if(faces.at(i).adjacentTrianglesId[j] != -1) {
                        nbAdj++;
                    }
                }
                if(nbAdj < min) {
                    min = nbAdj;
                    indice = i;
                }
            }
        }
        if(indice != -1) {
            int edge = -1;
            for(int i = 0; i < 3; i++) {
                if(faces.at(indice).adjacentTrianglesId[i] != -1) {
                    edge = i;
                }
            }
            if(edge != -1) {
                splitEdge(indice, edge);
            }
            else {
                faces.at(indice).isVisible = false;
            }
        }
    }
}


