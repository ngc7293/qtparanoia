#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QString>

class Track : public QObject {
    Q_OBJECT

private:
    unsigned int num_;
    unsigned int length_;
    QString title_;
    QString artist_;
    QString isrc_;

    QString path_;

public:
    Track(unsigned int num, QString title = "", QString artist = "", QString isrc = "");
    ~Track();

    void set_num(unsigned int num) { num_ = num; emit changed(); }
    void set_length(unsigned int length) { length_ = length; emit changed(); }

    void set_title(QString title)   { title_  = title; emit changed(); }
    void set_artist(QString artist) { artist_ = artist; emit changed(); }
    void set_isrc(QString isrc)     { isrc_   = isrc; emit changed(); }

    void set_path(QString path) { path_ = path; emit changed(); }

    unsigned int num() const { return num_; }
    unsigned int length() const { return length_; }

    QString title() const { return title_; }
    QString artist() const { return artist_; }
    QString isrc() const { return isrc_; }

    QString path() const { return path_; }

signals:
    void changed();
};

#endif