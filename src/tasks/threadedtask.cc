#include "tasks/threadedtask.h"

#include <iostream>
#include <thread>
#include <mutex>

ThreadedTask::ThreadedTask()
{
    quit_ = false;
}

ThreadedTask::~ThreadedTask()
{
    if (thread_) {
        thread_->join();
        delete thread_;
        thread_ = nullptr;
    }
}

void ThreadedTask::start()
{
    thread_ = new std::thread(&ThreadedTask::run, this);
}

bool ThreadedTask::is_stopped()
{
    quitlock_.lock();
    bool val = quit_;
    quitlock_.unlock();
    return val;
}

void ThreadedTask::stop()
{
    quitlock_.lock();
    quit_ = true;
    quitlock_.unlock();

    if (thread_) {
        thread_->join();
        delete thread_;
        thread_ = nullptr;
    }

    emit done(1);
}