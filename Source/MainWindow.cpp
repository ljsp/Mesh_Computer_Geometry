#include <iostream>

#include "Include/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->initializeGL();

    ui->exit_button->connect(ui->exit_button, SIGNAL(clicked()), this, SLOT(close()));

    ui->object_list->addItem(QString("queen"));
    ui->object_list->addItem(QString("cube"));
    //ui->object_list->addItem(QString("robot"));
    ui->object_list->connect(ui->object_list, SIGNAL(currentRowChanged(int)), this, SLOT(setCurrentMesh(int)));

    ui->wireframe_checkbox->connect(ui->wireframe_checkbox, SIGNAL(clicked()), this, SLOT(setWireFrame()));


    ui->load_button->connect(ui->load_button, SIGNAL(clicked()), this, SLOT(loadFile()));
    ui->save_button->connect(ui->save_button, SIGNAL(clicked()), this, SLOT(saveFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWireFrame() {
    ui->widget->isWireFrame = ui->wireframe_checkbox->isChecked();
}

void MainWindow::loadFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/lucas/Bureau/M2/GAM/Mesh_Computer_Geometry/Asset", tr("OFF Files (*.off)"), 0, QFileDialog::DontUseNativeDialog);
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
