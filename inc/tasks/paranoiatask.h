#ifndef PARANOIATASK_H
#define PARANOIATASK_H

#include "tasks/threadedtask.h"

#include <fstream>

#include "audiodisk.h"

class ParanoiaTask : public ThreadedTask {
    Q_OBJECT

private:
    AudioDisk* disk_;

public:
    ParanoiaTask(AudioDisk* disk);
    virtual ~ParanoiaTask();

protected:
    virtual void run();

private:
    void writeWavHeader(std::ofstream& file, unsigned int byte_count);

signals:
    void started(unsigned int sectors);
    void progress(unsigned int sector);
    void trackChanged(unsigned int track);
};

#endif // PARANOIATASK_H