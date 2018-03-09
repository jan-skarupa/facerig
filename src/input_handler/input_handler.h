#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QImage>
#include <QPixmap>

#include "opencv2/opencv.hpp"
#include "input_stream.h"


class InputHandler : public QObject
{
    Q_OBJECT
public:
    explicit InputHandler(QLabel* canvas, std::unique_ptr<input_stream> in_stream, QObject *parent = nullptr);

signals:

public slots:
    void open_stream();
    void close_stream();
    void get_image();

private:
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<input_stream> in_stream;
    QLabel* canvas;
};

#endif // CAMERA_H