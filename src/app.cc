#include <iostream>

#include <time.h>

#include <QStringListModel>

#include "tasks/cdinfotask.h"

#include "app.h"
#include "ui_app.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    time_t now = time(NULL);
    ui_->year_input->setMaximum(1900 + localtime(&now)->tm_year + 1);
    ui_->year_input->setValue(1900 + localtime(&now)->tm_year);

    ui_->progress_bar->setMinimum(0);
    ui_->progress_bar->setValue(0);

    QObject::connect(ui_->rip_button, SIGNAL(clicked()), this, SLOT(onRipButtonClicked()));
    QObject::connect(ui_->abort_button, SIGNAL(clicked()), this, SLOT(onAbortButtonClicked()));
    QObject::connect(ui_->device_dropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(onDeviceSelect(int)));
    model_ = new TagTableModel();
    ui_->tag_table->setModel(model_);

    cdinfo_ = new CDInfoTask();
    QObject::connect(cdinfo_, SIGNAL(done(int)), this, SLOT(onCDInfoReady(int)));
    cdinfo_->start();
    ui_->progress_bar->setRange(0, 0);
}

App::~App()
{
    delete model_;
    delete ui_;
}

void App::onRipButtonClicked()
{
}

void App::onAbortButtonClicked()
{
    if (cdinfo_) {
        cdinfo_->abort();
        delete cdinfo_;
    }
}

void App::onDeviceSelect(int index)
{
    AudioDisk* disk = disks_[index];
    ui_->album_input->setText(disk->title());
    ui_->artist_input->setText(disk->artist());
    ui_->progress_bar->setRange(0, disk->trackcount());
    model_->set_disk(disk);
}

void App::onCDInfoReady(int code)
{
    if (code == 0) {
        disks_ = cdinfo_->result();
        for (AudioDisk* disk : disks_) {
            ui_->device_dropdown->addItem(disk->title() + " (" + disk->device() + ")", disk->device());
        }
        ui_->progress_bar->setRange(0, 1);
    }

    delete cdinfo_;
}