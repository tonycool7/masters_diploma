#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(532, 515);
    move(QPoint(400, 50));
}

MainWindow::~MainWindow()
{
    delete ui;
}
