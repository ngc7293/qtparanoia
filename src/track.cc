#include "track.h"

Track::Track(unsigned int num, QString title, QString artist, QString isrc)
    : num_(num)
    , title_(title)
    , artist_(artist)
    , isrc_(isrc)
{
    if (title_ == "") {
        title_ = QString("Track %02").arg(num);
    }
}

Track::~Track()
{
}
