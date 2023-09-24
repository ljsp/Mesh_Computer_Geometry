#include "Include/glDisplayWidget.h"
#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#include <iostream>

#endif

#include "QDebug"

GLDisplayWidget::GLDisplayWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    // Update the scene
    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.start(16); // Starts or restarts the timer with a timeout interval of 16 milliseconds.
}

void GLDisplayWidget::initializeGL()
{
    glClearColor(0.2, 0.2, 0.2, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    //_geomWorld._mesh.loadOFF("../Asset/queen.off");
    _geomWorld.addMesh("../Asset/queen.off", true);
    _geomWorld.addMesh("../Asset/cube_maillage_triangles.off", true);
    //_geomWorld.addMesh("../Asset/champi.off", false);
    //_geomWorld._mesh.saveOFF();
}

void GLDisplayWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);

    glTranslated(_X, _Y, _Z);
    glRotatef(_angleY, 0.0f, 0.0f, 1.0f);
    glRotatef(_angleX, 0.0f, 1.0f, 0.0f);

    glColor3f(0, 1 ,0);

    if(isWireFrame)
        _geomWorld._meshes.at(currentMesh).drawMeshWireFrame();
    else
        _geomWorld._meshes.at(currentMesh).drawMesh();

    //_geomWorld._mesh.drawMeshWireFrame();
    //_geomWorld.drawWireFrame();
    //_geomWorld.draw();
}

void GLDisplayWidget::resizeGL(int width, int height){

    glViewport(0, 0, width, height); //Viewport in the world window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    update();
}

void GLDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _lastPosMouse = event->pos();
}

void GLDisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    qreal dx = event->position().x() - _lastPosMouse.x();
    qreal dy = event->position().y() - _lastPosMouse.y();

    if( event != NULL )
    {
        _angleX += dx;
        _angleY += dy;
        _lastPosMouse = event->pos();

        update();
    }
}

void GLDisplayWidget::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta();
    double stepZoom = 0.1;
    if (!numDegrees.isNull())
    {
        _Z = (numDegrees.x() > 0 || numDegrees.y() > 0) ? _Z + stepZoom : _Z - stepZoom;
    }
}

void GLDisplayWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_Z:
            _angleY += 5.0;
            break;
        case Qt::Key_S:
            _angleY -= 5.0;
            break;
        case Qt::Key_Q:
            _angleX -= 5.0;
            break;
        case Qt::Key_D:
            _angleX += 5.0;
            break;
        case Qt::Key_A:
            _Y -= 0.1;
            break;
        case Qt::Key_E:
            _Y += 0.1;
            break;
        case Qt::Key_Escape:
            exit(0);
        default:
            break;
    }
}
