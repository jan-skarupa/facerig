#include "pipeline_runner.h"


void InputRunner::start_stream()
{
    pipeline_mediator->open_stream();
    timer.start();
};

void InputRunner::stop_stream()
{
    timer.stop();
    pipeline_mediator->close_stream();
}