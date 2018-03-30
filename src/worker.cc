#include <iostream>

#include <QDir>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QThread>

#include "worker.h"

Worker::Worker(QString artist_folder, QString album_folder)
    : artist_folder_(artist_folder)
    , album_folder_(album_folder)
{
}

Worker::~Worker()
{
    if (cdparanoia_) {
        emit processAbort();
    }
}

void Worker::run()
{
    QDir folder(QDir::current());

    // Create artist folder
    if (!folder.mkdir(artist_folder_) || !folder.cd(artist_folder_)) {
        std::cerr << "Could not move to folder \'" << artist_folder_.toStdString() << "\'" << std::endl;
        return;
    }

    // Create album folder
    if (!folder.mkdir(album_folder_) || !folder.cd(album_folder_)) {
        std::cerr << "Could not move to folder \'" << album_folder_.toStdString() << "\'"  << std::endl;
        return;
    }

    // Create and launch Process
    cdparanoia_ = new QProcess();

    cdparanoia_->setProgram("cdparanoia");
    cdparanoia_->setArguments(QStringList("-B"));
    cdparanoia_->setWorkingDirectory(folder.absolutePath());

    connect(cdparanoia_, SIGNAL(readyReadStandardError()), this, SLOT(processOuput()));
    connect(cdparanoia_, SIGNAL(readyReadStandardOutput()), this, SLOT(processOuput()));
    connect(cdparanoia_, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    connect(this, SIGNAL(processAbort()), cdparanoia_, SLOT(kill()));

    cdparanoia_->start();
    emit tracks(0);
}

void Worker::processOuput()
{
    // Apparently CDParanoia prints to stderr...
    QString stderr = cdparanoia_->readAllStandardError();

    QRegExp count("to sector\\s*\\d+\\s*\\(track\\s*(\\d+)");
    QRegExp current("outputting to track(\\d\\d)\\.");

    if (count.indexIn(stderr) != -1) {
        emit tracks(count.capturedTexts()[1].toInt());
    }
    if (current.indexIn(stderr) != -1) {
        emit progress(current.capturedTexts()[1].toInt());
    }
}

void Worker::processFinished(int code)
{
    std::cout << "done" << std::endl;
    emit done(code);
    delete cdparanoia_;
}