#include "tasks/task.h"

#include <iostream>
#include <thread>
#include <mutex>

Task::Task()
{
}

Task::~Task()
{
    if (thread_) {
        thread_->join();
        delete thread_;
        thread_ = nullptr;
    }
}

void Task::start()
{
    thread_ = new std::thread(&Task::run, this);
}

bool Task::is_stopped()
{
    quitlock_.lock();
    bool val = quit_;
    quitlock_.unlock();
    return val;
}

void Task::stop()
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