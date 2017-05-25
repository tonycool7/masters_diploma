#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

int MainWindow::tab = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mysqlSettings *m = new mysqlSettings();
    postgresqlSettings *p = new postgresqlSettings();
    setFixedSize(532, 515);
    move(QPoint(400, 50));

    connect(ui->manual_mysql, SIGNAL(clicked()), m, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(int value)
{
    tab = value;
}
