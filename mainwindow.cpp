#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysqlsettings.h"
#include "ui_mysqlsettings.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mysqlSettings *m = new mysqlSettings();
    Ui::mysqlSettings *mi;
    mi->setupUi(m);
    postgresqlSettings *p = new postgresqlSettings();
    DatabaseManager *db = new DatabaseManager();
    setFixedSize(532, 515);
    move(QPoint(400, 50));
    connect(ui->postgre_proceed_btn, SIGNAL(clicked()), p, SLOT(show()));
    connect(ui->mysql_proceed_btn, SIGNAL(clicked()), m, SLOT(show()));
    connect(mi->mysql_ok_btn, SIGNAL(clicked()), this, SLOT(connectToMysqlServer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToMysqlServer()
{
    qDebug() << "Dasd";
}
