#include "pipeline_qt_mediator.h"


void QtMediator::run_pipeline()
{
    input_pipeline.lock()->run_pipeline();
    render_pipeline_output();
}

void QtMediator::render_pipeline_output()
{
    cv::Mat image = input_pipeline.lock()->get_frame();

    QImage imdisplay((uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    canvas->setPixmap(QPixmap::fromImage(imdisplay));
}


std::shared_ptr<QtMediator> make_qt_mediator(std::shared_ptr<InputPipeline> input_pipeline, QLabel *canvas)
{
    return std::make_shared<QtMediator>(input_pipeline, canvas);
}
