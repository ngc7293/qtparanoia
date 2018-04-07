#include <iostream>
#include <iomanip>
#include <sstream>

#include <time.h>

#include <QStringListModel>

#include "tasks/cdinfotask.h"

#include "app.h"
#include "ui_app.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
    , paranoia_(nullptr)
    , selected_(nullptr)
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
    QObject::connect(ui_->album_input, SIGNAL(textChanged(QString)), this, SLOT(onAlbumInfoChanged()));
    QObject::connect(ui_->artist_input, SIGNAL(textChanged(QString)), this, SLOT(onAlbumInfoChanged()));
    QObject::connect(ui_->year_input, SIGNAL(valueChanged(int)), this, SLOT(onAlbumInfoChanged()));

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
    ui_->progress_bar->setRange(0, 0);
    ui_->device_dropdown->setDisabled(true);
    ui_->rip_button->setDisabled(true);

    paranoia_ = new ParanoiaTask(selected_);
    QObject::connect(paranoia_, SIGNAL(started(unsigned int)), this, SLOT(onParanoiaStarted(unsigned int)));
    QObject::connect(paranoia_, SIGNAL(progress(unsigned int)), this, SLOT(onParanoiaProgress(unsigned int)));
    QObject::connect(paranoia_, SIGNAL(trackChanged(unsigned int)), this, SLOT(onParanoiaTrackChange(unsigned int)));
    QObject::connect(paranoia_, SIGNAL(done(int)), this, SLOT(onParanoiaDone(int)));
    paranoia_->start();
}

void App::onAbortButtonClicked()
{
    ui_->device_dropdown->setDisabled(false);
    ui_->rip_button->setDisabled(false);

    if (cdinfo_) {
        cdinfo_->stop();
        delete cdinfo_;
        paranoia_ = nullptr;
    }

    if (paranoia_) {
        paranoia_->stop();
        delete paranoia_;
        paranoia_ = nullptr;
    }
}

void App::onAlbumInfoChanged()
{
    if (selected_) {
        selected_->set_title(ui_->album_input->text());
        selected_->set_artist(ui_->artist_input->text());
        selected_->set_year(ui_->year_input->value());
    }
}

void App::onDeviceSelect(int index)
{
    selected_ = disks_[index];
    ui_->album_input->setText(selected_->title());
    ui_->artist_input->setText(selected_->artist());
    ui_->progress_bar->setRange(0, selected_->trackcount());
    model_->set_disk(selected_);
}

void App::onCDInfoReady(int code)
{
    if (code == 0) {
        disks_ = cdinfo_->result();
        for (AudioDisk* disk : disks_) {
            ui_->device_dropdown->addItem(disk->title() + " (" + disk->device() + ")", disk->device());
        }
        selected_ = disks_[0];
        ui_->progress_bar->setRange(0, selected_->trackcount());
    }

    delete cdinfo_;
    cdinfo_ = nullptr;
}

void App::onParanoiaStarted(unsigned int sectors)
{
    ui_->progress_bar->setRange(0, sectors);
    std::stringstream ss;
    ss << 0 << "/" << selected_->trackcount();
    ui_->progress_bar->setFormat(ss.str().c_str());
}

void App::onParanoiaProgress(unsigned int sector)
{
    ui_->progress_bar->setValue(sector);
}

void App::onParanoiaTrackChange(unsigned int track)
{
    std::stringstream ss;
    ss << track << "/" << selected_->trackcount();
    ui_->progress_bar->setFormat(ss.str().c_str());
}

void App::onParanoiaDone(int code)
{
    ui_->progress_bar->setRange(0, 1);
    ui_->progress_bar->setFormat("%v/%m");

    delete paranoia_;
    paranoia_ = nullptr;
}