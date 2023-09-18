#include "Include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Close window
    ui->pushButton_2->connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(close()));
    ui->menuBar->connect(ui->actionLoad_Mesh, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
