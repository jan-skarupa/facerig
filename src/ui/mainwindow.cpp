#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    input_pipeline = make_default_input_pipeline();
    input_qt_mediator = make_qt_mediator(input_pipeline, ui->display);
    input_runner = std::make_unique<InputRunner>(input_qt_mediator);

    connect(ui->cam_start_btn, SIGNAL(clicked(bool)), input_runner.get(), SLOT(start_stream()));
    connect(ui->cam_stop_btn, SIGNAL(clicked(bool)), input_runner.get(), SLOT(stop_stream()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
