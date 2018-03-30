#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QThread>
#include <QStringListModel>

#include "worker.h"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;

    Worker* worker_;
    QStringListModel* model_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

private slots:
    void onRipButtonClicked();
    void onTrackCount(int count);
};

#endif // APP_H
