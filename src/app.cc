#include <iostream>

#include <time.h>

#include <QStringListModel>

#include "app.h"
#include "ui_app.h"

#include "worker.h"

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

    model_ = new QStringListModel();

    QObject::connect(ui_->rip_button, SIGNAL(clicked()), this, SLOT(onRipButtonClicked()));
}

App::~App()
{
    if (worker_) {
        delete worker_;
    }
    delete ui_;
    delete model_;
}

void App::onRipButtonClicked()
{
    QString artist_folder;
    QString album_folder;

    artist_folder = ui_->artist_input->text();
    album_folder = ui_->album_input->text() + " (" + ui_->year_input->text() + ")";
    worker_ = new Worker(artist_folder, album_folder);
    QObject::connect(worker_, SIGNAL(tracks(int)), ui_->progress_bar, SLOT(setMaximum(int)));
    QObject::connect(worker_, SIGNAL(tracks(int)), this, SLOT(onTrackCount(int)));
    QObject::connect(worker_, SIGNAL(progress(int)), ui_->progress_bar, SLOT(setValue(int)));
    worker_->run();
}

void App::onTrackCount(int count)
{
    QStringList list;

    for (int i = 1; i <= count; ++i)
        list << (QString("track%02").arg(i));
    model_->setStringList(list);
    ui_->track_list->setModel(model_);
}