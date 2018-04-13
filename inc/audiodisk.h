#ifndef CD_H
#define CD_H

#include <QDir>
#include <QString>

#include "track.h"

class AudioDisk : public QObject {
    Q_OBJECT
private:
    std::vector<Track*> tracks_;

    // Metadata
    QString title_;
    QString artist_;
    int year_;

    // Technical attributes
    QString device_;
    std::vector<QDir> locations_;

public:
    AudioDisk(QString device, QString title = "", QString artist = "");
    ~AudioDisk();

    void add_track(Track* track) { tracks_.push_back(track); emit changed(); }

    Track* track(int index) { return tracks_[index]; }
    std::vector<Track*> tracks() { return tracks_; }
    unsigned int trackcount() { return tracks_.size(); }

    QString title() const { return title_; }
    QString artist() const { return artist_; }
    int year() const { return year_;  }

    QString device() const { return device_; }

    

public slots:
    void set_tracks(std::vector<Track*> tracks) { tracks_ = tracks; emit changed(); }

    void set_title(QString title) { title_ = title; emit changed(); }
    void set_artist(QString artist) { artist_ = artist; emit changed(); }
    void set_year(int year) { year_ = year; }

signals:
    void changed();
};

#endif