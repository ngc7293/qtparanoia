#ifndef CDINFOTASK_H
#define CDINFOTASK_H

#include "task.h"

#include <string>

#include "audiodisk.h"

class CDInfoTask : public Task {
private:

    std::vector<AudioDisk*> disks_;

public:
    CDInfoTask();
    ~CDInfoTask();

    std::vector<AudioDisk*> result() { return disks_; }

protected:
    virtual void run();

private:
    void readInfo(std::string device);
};

#endif // CDINFOTASK_H