#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT

private:
    QString artist_folder_;
    QString album_folder_;
    QProcess* cdparanoia_;

public:
    Worker(QString artist_folder, QString album_folder);
    ~Worker();

private slots:
    void processOuput();
    void processFinished(int code);

public slots:
    void run();
    void abort();

signals:
    void sectors(int count);
    void tracks(int count);
    void progress(int sectors);
    void done(int code);
};

#endif // WORKER_H