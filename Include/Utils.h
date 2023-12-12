//
// Created by lucas on 18/09/23.
//

#ifndef MESH_COMPUTATIONAL_GEOMETRY_UTILS_H
#define MESH_COMPUTATIONAL_GEOMETRY_UTILS_H

#include "Include/Structures.h"
#include "Mathematics.h"
#include <QOpenGLWidget>

inline void glPointDraw(const Point & p) {
    glVertex3f(p._x, p._y, p._z);
}

enum DrawMode {
    DRAW_MESH,
    DRAW_MESH_ITERATOR,
    DRAW_MESH_CIRCULATOR,
    DRAW_MESH_WIREFRAME,
    DRAW_MESH_LAPLACIAN,
    DRAW_MESH_NORMALS,
};

inline std::array<float, 3> HSV(float val){
    float X = (1 - std::abs(fmod( val / 60, 2) - 1));

    if(val < 60) return {0, X,1};
    if(val < 120) return {0, 1,X};
    if(val < 180) return {X, 1,0};
    if(val < 240) return {1, X,0};
    if(val < 300) return {1, 0,X};
    if(val < 360) return {X, 0,1};

    float V =  1 - 1 / ( 1 + val / 10);
    return {V, V, V};
}

inline double cotan(const Point& a, const Point& b) {
    return Math::Dot(a,b) / Math::Norm(Math::Cross(a,b));
}

inline double triangleArea(const Point& p1, const Point& p2, const Point& p3) {
    Point vec1 = p2 - p1;
    Point vec2 = p3 - p1;
    Point cross = Math::Cross(vec1, vec2);
    return Math::Norm(cross);
}

inline int Orientation(Point a, Point b, Point c){

    double dx1 = b._x - a._x;
    double dy1 = b._y - a._y;
    double dx2 = c._x - a._x;
    double dy2 = c._y - a._y;

    double crossProduct = (dx1 * dy2) - (dx2 * dy1);

    if (crossProduct > 0) {
        return 1.0; // Counter-clockwise
    } else if (crossProduct < 0) {
        return -1.0; // Clockwise
    } else {
        return 0.0; // Aligned
    }
}

inline int pointPosition(const Point& A, const Point& B, const Point& C, const Point& P) {
    // Fonction pour vérifier la position d'un point par rapport à un triangle.
    // Calculez l'orientation des trois côtés du triangle.
    int orientABP = Orientation(A, B, P);
    int orientBCP = Orientation(B, C, P);
    int orientCAP = Orientation(C, A, P);

    // Vérifiez si le point est situé à l'intérieur du triangle.
    if (orientABP == orientBCP && orientBCP == orientCAP) {
        if (orientABP == 0) {
            return 0; // Le point est sur un bord du triangle.
        } else {
            return 1; // Le point est à l'intérieur du triangle.
        }
    }

    return -1; // Le point est à l'extérieur du triangle.
}


#endif //MESH_COMPUTATIONAL_GEOMETRY_UTILS_H
