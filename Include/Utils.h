//
// Created by lucas on 18/09/23.
//

#ifndef MESH_COMPUTATIONAL_GEOMETRY_UTILS_H
#define MESH_COMPUTATIONAL_GEOMETRY_UTILS_H

#include "Include/Structures.h"
#include <QOpenGLWidget>

inline void glPointDraw(const Point & p) {
    glVertex3f(p._x, p._y, p._z);
}

enum DrawMode {
    DRAW_MESH,
    DRAW_MESH_ITERATOR,
    DRAW_MESH_CIRCULATOR,
    DRAW_MESH_WIREFRAME
};

#endif //MESH_COMPUTATIONAL_GEOMETRY_UTILS_H
