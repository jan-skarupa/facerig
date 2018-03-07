#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cam = new Camera(ui->display);
    connect(ui->cam_start_btn, SIGNAL(clicked(bool)), cam, SLOT(start_camera()));
    connect(ui->cam_stop_btn, SIGNAL(clicked(bool)), cam, SLOT(stop_camera()));
    connect(ui->cam_colormode_btn, SIGNAL(clicked(bool)), cam, SLOT(toogle_colormode()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
