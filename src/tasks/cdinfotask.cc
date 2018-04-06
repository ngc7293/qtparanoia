#include "tasks/cdinfotask.h"

#include <iostream>
#include <iomanip>

#include <cdio/cdio.h>
#include <cdio/cd_types.h>

CDInfoTask::CDInfoTask()
{
}

CDInfoTask::~CDInfoTask()
{
}

void CDInfoTask::run()
{
    // Find all Audio CDs
    char **drives = cdio_get_devices_with_cap(NULL, CDIO_FS_AUDIO, false);

    // Read info for each drive
    for (int i = 0; drives[i] != NULL; ++i) {
        if (drives[i] != nullptr) {
            readInfo(std::string(drives[i]));
        }
    }

    emit done(0);
}

void CDInfoTask::readInfo(std::string device)
{
    CdIo_t* cdio = cdio_open(device.c_str(), DRIVER_UNKNOWN);
    if (!cdio) {
        std::cerr << "No such device: " << device << std::endl;
        return;
    }

    // Create Audio disk
    AudioDisk* disk = new AudioDisk(device.c_str());

    // Get CDInfo
    cdtext_t* info = cdio_get_cdtext(cdio, 0);

    // Set disk (album) metadata
    // Default on unknown if field is missing
    disk->set_title(info && info->field[9] ? info->field[9] : "unknown album");
    disk->set_artist(info && info->field[6] ? info->field[6] : "unknown artist");

    // Create CDInfo for each track
    track_t first = cdio_get_first_track_num(cdio);
    track_t last = cdio_get_last_track_num(cdio);

    QString title;
    QString artist;
    QString isrc;
    for (track_t track = first; track <= last; ++track) {
        info = cdio_get_cdtext(cdio, track);
        title = info && info->field[9] ? info->field[9] : QString("track%02").arg(track);
        artist = info && info->field[6] ? info->field[6] : "unknown artist";
        isrc = info && info->field[5] ? info->field[5] : "";
        disk->add_track(new Track(track, title, artist, isrc));
    }

    // Cleanup
    cdio_destroy(cdio);
    disks_.push_back(disk);
}