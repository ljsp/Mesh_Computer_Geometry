#include <iostream>

#include "Include/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->exit_button->connect(ui->exit_button, SIGNAL(clicked()), this, SLOT(close()));

    ui->object_list->addItem(QString("queen"));
    ui->object_list->addItem(QString("cube"));
    ui->object_list->addItem(QString("square"));
    ui->object_list->connect(ui->object_list, SIGNAL(currentRowChanged(int)), this, SLOT(setCurrentMesh(int)));

    ui->wireframe_checkbox->connect(ui->wireframe_checkbox, SIGNAL(clicked()), this, SLOT(setWireFrame()));
    ui->inf_point_checkbox->connect(ui->inf_point_checkbox, SIGNAL(clicked()), this, SLOT(setInfPoint()));

    ui->load_button->connect(ui->load_button, SIGNAL(clicked()), this, SLOT(loadFile()));
    ui->save_button->connect(ui->save_button, SIGNAL(clicked()), this, SLOT(saveFile()));

    ui->it_cf_radio_none->connect(ui->it_cf_radio_none, SIGNAL(clicked()), this, SLOT(setDrawModeNone()));
    ui->it_cf_radio_itf->connect(ui->it_cf_radio_itf, SIGNAL(clicked()), this, SLOT(setDrawModeIterator()));
    ui->it_cf_radio_cf->connect(ui->it_cf_radio_cf, SIGNAL(clicked()), this, SLOT(setDrawModeCirculator()));
    ui->it_cf_prev_button->connect(ui->it_cf_prev_button, SIGNAL(clicked()), this, SLOT(drawIteratorCirculatorPrev()));
    ui->it_cf_next_button->connect(ui->it_cf_next_button, SIGNAL(clicked()), this, SLOT(drawIteratorCirculatorNext()));

    ui->splitButton->connect(ui->splitButton, SIGNAL(clicked()), this, SLOT(splitTriangle()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWireFrame() {
    ui->widget->isWireFrame = ui->wireframe_checkbox->isChecked();
}

void MainWindow::loadFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home/lucas/Bureau/M2/GAM/Mesh_Computer_Geometry/Asset",
                                                    tr("OFF Files (*.off)"), 0,
                                                    QFileDialog::DontUseNativeDialog);
    ui->widget->_geomWorld.addMesh(filename.toStdString().c_str(), false);
    QString name = filename.split("/").last().remove(".off");
    ui->object_list->addItem(name);
    ui->widget->currentMesh = ui->object_list->count() + 1;
}

void MainWindow::saveFile() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("OFF Files (*.off)"), 0, QFileDialog::DontUseNativeDialog);
    ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).saveOFF(filename.toStdString().c_str());
}

void MainWindow::setCurrentMesh(int index) {
    ui->widget->currentMesh = index;
}

void MainWindow::setInfPoint() {
    ui->widget->isInfPoint = ui->inf_point_checkbox->isChecked();
}

void MainWindow::setDrawModeNone() {
    ui->widget->drawMode = DRAW_MESH;
}

void MainWindow::setDrawModeIterator() {
    ui->widget->drawMode = DRAW_MESH_ITERATOR;
}

void MainWindow::setDrawModeCirculator() {
    ui->widget->drawMode = DRAW_MESH_CIRCULATOR;
}

void MainWindow::drawIteratorCirculatorPrev() {
    if(ui->widget->drawMode == DRAW_MESH_ITERATOR)
        --ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).itf;

    if(ui->widget->drawMode == DRAW_MESH_CIRCULATOR)
        --ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).cf;
}

void MainWindow::drawIteratorCirculatorNext() {
    if(ui->widget->drawMode == DRAW_MESH_ITERATOR)
        ++ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).itf;

    if(ui->widget->drawMode == DRAW_MESH_CIRCULATOR)
        ++ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).cf;
}

void MainWindow::splitTriangle() {

    /*int numberSplit = ui->numberSplitSpinBox->value();
    for (int i = 0; i < numberSplit; ++i) {
        double x = (double) rand() / RAND_MAX;
        double y = (double) rand() / RAND_MAX;
        int face = rand() % 2;

        ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).splitTriangle(face,Point(x,y,0));
    }*/

    ui->widget->_geomWorld._meshes.at(ui->widget->currentMesh).flipEdge(0,1);
}

