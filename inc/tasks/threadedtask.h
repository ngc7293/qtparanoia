#ifndef THREADEDTASK_H
#define THREADEDTASK_H


#include "task.h"

#include <thread>

#include <mutex>

class ThreadedTask : public Task {
    Q_OBJECT

protected:
    std::thread* thread_;
    std::mutex quitlock_;

    bool quit_;

public:
    ThreadedTask();
    virtual ~ThreadedTask();

    virtual void start();

protected:
    virtual void run() = 0;
    bool is_stopped();

public slots:
    virtual void stop();
};

#endif // THREADEDTASK_H