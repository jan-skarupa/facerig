#ifndef FACERIG_MOCK_MEDIATOR_H
#define FACERIG_MOCK_MEDIATOR_H

#include "pipeline_ui_mediator.h"
#include "../render/render_facade.h"


class MockMediator : public PipelineUiMediator {
public:
    MockMediator(const std::shared_ptr<InputPipeline> &input_pipeline_ptr)
            : PipelineUiMediator(input_pipeline_ptr) {}

    void run_pipeline() override;
    void render_pipeline_output() override;

    void render_pipeline();
    std::shared_ptr<RenderFacade> render;
};


std::shared_ptr<MockMediator> make_mock_mediator(std::shared_ptr<InputPipeline> input_pipeline);

#endif //FACERIG_MOCK_MEDIATOR_H
