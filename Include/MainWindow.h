#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void loadFile();
    void saveFile();
    void setDraw();
    void setInfPoint();
    void setStitching();
    void setDrawModeNone();
    void setDrawModeIterator();
    void setDrawModeCirculator();
    void drawIteratorCirculatorPrev();
    void drawIteratorCirculatorNext();
    void setCurrentMesh(int index);
    void flipEdge();
    void splitTriangle();
    void makeDelauney();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
