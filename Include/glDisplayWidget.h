#ifndef GLDISPLAYWIDGET_H
#define GLDISPLAYWIDGET_H

#include <QOpenGLWidget> // Module QtOpengL (classes QGLxxx in Qt4),
                         // with widget and rendering classes descending from QGLWidget,
                         // deprecated for module QtGui (classes QOpenGLxxx )
                         // and module widgets (QWidget, QGraphicsView).

#include <QtWidgets>
#include <QTimer>
#include "GeometricWorld.h"
#include "Mesh.h"

enum DrawMode {
    DRAW_MESH = 0,
    DRAW_MESH_ITERATOR = 1,
    DRAW_MESH_CIRCULATOR = 2,
    DRAW_MESH_WIREFRAME,
    DRAW_TRIANGLE,
    DRAW_INFPOINT
};

class GLDisplayWidget : public QOpenGLWidget
{
public:
    explicit GLDisplayWidget(QWidget *parent = 0);

    void initializeGL(); // The scene may be initialized in this function since the GeometricWorld is a data member...
    void paintGL(); // Display the scene Gl
    void resizeGL(int width, int height);

    bool isWireFrame = false;
    bool isInfPoint = false;
    DrawMode drawMode = DRAW_MESH;
    int currentMesh = 0;
    GeometricWorld _geomWorld;

protected:
    // Mouse Management
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:

    QTimer _timer; // To update the scene
    float _X = 0.f, _Y = 0.f ,_Z = 0.f; // Translation
    float _angleX = 0.f, _angleY = 0.f; // Rotation

    QPoint _lastPosMouse; // To keep the last position of the mouse
};

#endif // GLDISPLAYWIDGET_H
