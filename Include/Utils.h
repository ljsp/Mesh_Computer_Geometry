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

#endif //MESH_COMPUTATIONAL_GEOMETRY_UTILS_H
