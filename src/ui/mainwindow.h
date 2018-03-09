#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../input_handler/input_handler.h"
#include "../input_handler/input_stream.h"
#include "../input_handler/face_detector.h"

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
    InputHandler*   in_handler;

private slots:
};

#endif // MAINWINDOW_H
