#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mysqlSettings *m = new mysqlSettings();
    postgresqlSettings *p = new postgresqlSettings();
    setFixedSize(532, 515);
    move(QPoint(400, 50));
    connect(ui->postgre_proceed_btn, SIGNAL(clicked()), p, SLOT(show()));
    connect(ui->mysql_proceed_btn, SIGNAL(clicked()), m, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
