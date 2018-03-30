#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QThread>

#include "worker.h"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;

    QThread* thread_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

private slots:
    void onRipButtonClicked();

signals:
    void startWorker(QString artist_folder, QString album_folder);
};

#endif // APP_H
