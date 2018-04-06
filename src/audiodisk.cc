#include "audiodisk.h"

AudioDisk::AudioDisk(QString device, QString title, QString artist)
    : device_(device)
    , title_(title)
    , artist_(artist)
{
}

AudioDisk::~AudioDisk()
{
    while (tracks_.size()) {
        delete tracks_[0];
        tracks_.erase(tracks_.begin());
    }
}