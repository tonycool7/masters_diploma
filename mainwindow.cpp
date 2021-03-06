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
    connect(ui->postgre_proceed_btn, SIGNAL(clicked()), p, SLOT(show()));
    connect(ui->mainwindowTab, SIGNAL(currentChanged(int)), SLOT(update(int)));
    connect(ui->mysql_proceed_btn, SIGNAL(clicked()), m, SLOT(show()));
    connect(ui->mysql_man_remotebkp_radio, SIGNAL(toggled(bool)), m, SLOT(enableRemoteManaulBackup(bool)));
    connect(ui->postgre_man_remotebkp_radio, SIGNAL(toggled(bool)), p, SLOT(enableRemoteManaulBackup(bool)));

    qDebug() << ui->mainwindowTab->currentIndex();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(int value)
{
    tab = value;
}
