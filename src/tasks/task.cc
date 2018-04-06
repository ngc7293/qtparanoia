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
    }
}

void Task::start()
{
    thread_ = new std::thread(&Task::run, this);
}

bool Task::aborted()
{
    bool aborted;
    quitlock_.lock();
    aborted = quit_;
    quitlock_.unlock();
    return aborted;
}

void Task::abort()
{
    quitlock_.lock();
    quit_ = true;
    quitlock_.unlock();
    delete this;
}