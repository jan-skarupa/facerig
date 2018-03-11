#ifndef FACERIG_INSTREAM_RUNNER_H
#define FACERIG_INSTREAM_RUNNER_H

#define FPS 30

#include <QObject>
#include <QTimer>
#include "../input_pipeline/mediators/pipeline_ui_mediator.h"
#include "../input_pipeline/mediators/qt_mediator.h"


class InputRunner : public QObject
{
Q_OBJECT
public:
    InputRunner(std::shared_ptr<QtMediator> mediator, QObject *parent = nullptr)
    {
        pipeline_mediator = std::move(mediator);
        timer.setInterval(1000/FPS);
        connect(&timer, SIGNAL(timeout()), pipeline_mediator.get(), SLOT(run_pipeline()));
    }

public slots:
    void start_stream();
    void stop_stream();

private:
    QTimer timer;
    std::shared_ptr<QtMediator> pipeline_mediator;
};


#endif //FACERIG_INSTREAM_RUNNER_H