#ifndef TASK_H
#define TASK_H

#include <thread>

#include <mutex>

#include <QObject>

class Task : public QObject {
    Q_OBJECT

protected:
    std::thread* thread_;
    std::mutex resultlock_;
    std::mutex quitlock_;

    bool quit_;

public:
    Task();
    ~Task();

    void start();

protected:
    virtual void run() = 0;
    bool aborted();

public slots:
    void abort();

signals:
    void done(int code);
};

#endif // TASK_H