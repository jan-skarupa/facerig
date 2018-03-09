#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto in_stream = make_camera_stream();
    auto face_detector = make_harr_face_detector("../resources/face_detection/haarcascade_frontalface_alt.xml");
    in_handler = new InputHandler(ui->display, std::move(in_stream), std::move(face_detector));

    connect(ui->cam_start_btn, SIGNAL(clicked(bool)), in_handler, SLOT(open_stream()));
    connect(ui->cam_stop_btn, SIGNAL(clicked(bool)), in_handler, SLOT(close_stream()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
