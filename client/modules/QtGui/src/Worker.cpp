#include "Worker.hpp"
#include <iostream>
Worker::Worker(std::function<void(std::string, std::string)> runFunction, std::string arg1, std::string arg2)
    : arg1_(arg1)
    , arg2_(arg2)
{
    runFunction_ = runFunction;
}

Worker::~Worker()
{
}

void Worker::process()
{
    runFunction_(arg1_, arg2_);
    emit finished();
}