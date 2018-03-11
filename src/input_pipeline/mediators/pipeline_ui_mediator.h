#ifndef FACERIG_PIPELINE_UI_MEDIATOR_H
#define FACERIG_PIPELINE_UI_MEDIATOR_H

#include <opencv2/opencv.hpp>
#include <memory>
#include "../pipeline.h"

class PipelineUiMediator {
public:
    explicit PipelineUiMediator(std::shared_ptr<InputPipeline> input_pipeline_ptr) {
        input_pipeline = input_pipeline_ptr;
    };

    virtual void open_stream() final {
        input_pipeline.lock()->open_stream();
    };
    virtual void close_stream() final {
        input_pipeline.lock()->close_stream();
    };
    virtual void run_pipeline() = 0;
    virtual void render_pipeline_output() = 0;

protected:
    std::weak_ptr<InputPipeline> input_pipeline;
};


#endif //FACERIG_PIPELINE_UI_MEDIATOR_H
