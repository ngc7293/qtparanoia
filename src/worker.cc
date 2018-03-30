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
    
}

void Worker::run()
{
    QDir folder(QDir::current());

    // Create artist folder
    if (!folder.mkdir(artist_folder_) || !folder.cd(artist_folder_)) {
        std::cout << "Could not move to folder \'" << artist_folder_.toStdString() << "\'";
        return;
    }

    // Create album folder
    if (!folder.mkdir(album_folder_) || !folder.cd(album_folder_)) {
        std::cout << "Could not move to folder \'" << album_folder_.toStdString() << "\'";
        return;
    }

    // Create and launch Process
    cdparanoia_ = new QProcess();

    cdparanoia_->setProgram("cdparanoia");
    cdparanoia_->setArguments(QStringList("-B"));

    connect(cdparanoia_, SIGNAL(readyReadStandardError()), this, SLOT(processOuput()));
    connect(cdparanoia_, SIGNAL(readyReadStandardOutput()), this, SLOT(processOuput()));
    connect(cdparanoia_, SIGNAL(finished(int)), this, SLOT(processFinished(int)));

    cdparanoia_->start();
    cdparanoia_->waitForFinished();
}

void Worker::abort()
{
    if (cdparanoia_)
        cdparanoia_->kill();
}

void Worker::processOuput()
{
    QString stderr = cdparanoia_->readAllStandardError();
    QString stdout = cdparanoia_->readAllStandardOutput();

    QRegExp sectors("^\\s*to sector\\s*(\\d+)");
    // QRegExp current("^\\s*( == PROGRESS == \\[.*\\| (\\d+)");
    // QRegExp progress("PROGRESS");

    std::cout << "\"" << stderr.toStdString() << "\"" << std::endl;
    //if (sectors.indexIn(stderr) != -1) {
    //emit Worker::sectors(sectors.capturedTexts()[0].toInt());
    //}
    // if (current.indexIn(stderr) != -1) {
    //     emit Worker::progress(sectors.capturedTexts()[0].toInt());
    // }
    // if (progress.indexIn(stderr) != -1) {
    //     std::cout << "PROGRESS" << std::endl;
    // }

}

void Worker::processFinished(int code)
{
    delete cdparanoia_;

    std::cout << "Ended with code: " << code << std::endl;
}