#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "pipeline_runner.h"
#include "../input_pipeline/pipeline.h"
#include "../input_pipeline/mediators/qt_mediator.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    std::unique_ptr<InputRunner> input_runner;
    std::shared_ptr<InputPipeline> input_pipeline;
    std::shared_ptr<QtMediator> input_qt_mediator;

private slots:
};

#endif // MAINWINDOW_H
