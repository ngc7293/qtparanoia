#ifndef APP_H
#define APP_H

#include <QMainWindow>

#include "tasks/cdinfotask.h"
#include "tasks/paranoiatask.h"
#include "model/tagtablemodel.h"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;

    // Data
    AudioDisk* selected_;
    std::vector<AudioDisk*> disks_;
    TagTableModel* model_;

    // Tasks
    CDInfoTask* cdinfo_;
    ParanoiaTask* paranoia_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

private slots:
    void onRipButtonClicked();
    void onAbortButtonClicked();

    void onDeviceSelect(int index);
    void onCDInfoReady(int code);

    void onParanoiaStarted(unsigned int sectors);
    void onParanoiaProgress(unsigned int sector);
    void onParanoiaTrackChange(unsigned int track);
    void onParanoiaDone(int code);
};

#endif // APP_H
