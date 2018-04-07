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

bool Task::aborted()
{
    bool aborted;
    quitlock_.lock();
    aborted = quit_;
    quitlock_.unlock();
    return aborted;
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