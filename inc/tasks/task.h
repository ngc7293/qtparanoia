#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task : public QObject {
    Q_OBJECT

public:
    virtual void start() = 0;

public slots:
    virtual void stop() = 0;

signals:
    void done(int code);
};

#endif // TASK_H