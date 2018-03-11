#ifndef FACERIG_QT_MEDIATOR_H
#define FACERIG_QT_MEDIATOR_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QLabel>

#include "pipeline_ui_mediator.h"


class QtMediator : public QObject, public PipelineUiMediator
{
Q_OBJECT
public:
    explicit QtMediator(std::shared_ptr<InputPipeline> pipeline, QLabel* canvas)
            : PipelineUiMediator(pipeline), canvas(canvas) {};

    void open_stream() override;
    void close_stream() override;
    void render_pipeline_output() override;

public slots:
    void run_pipeline() override;

private:
    QLabel* canvas;
};


std::shared_ptr<QtMediator> make_qt_mediator(std::shared_ptr<InputPipeline> input_pipeline, QLabel *canvas);


#endif //FACERIG_QT_MEDIATOR_H
