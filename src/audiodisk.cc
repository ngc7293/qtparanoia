#include "audiodisk.h"

#include <ctime>

AudioDisk::AudioDisk(QString device, QString title, QString artist)
    : device_(device)
    , title_(title)
    , artist_(artist)
{
    time_t now = time(NULL);
    year_ = 1900 + localtime(&now)->tm_year + 1;
}

AudioDisk::~AudioDisk()
{
    while (tracks_.size()) {
        delete tracks_[0];
        tracks_.erase(tracks_.begin());
    }
}