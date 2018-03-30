#include <iostream>

#include <time.h>

#include "app.h"
#include "ui_app.h"

#include "worker.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    time_t now = time(NULL);

    ui_->year_input->setValue(1900 + localtime(&now)->tm_year);
    ui_->year_input->setMaximum(ui_->year_input->value() + 1);
    QObject::connect(ui_->rip_button, SIGNAL(clicked()), this, SLOT(onRipButtonClicked()));

    ui_->progress_bar->setMinimum(0);
    ui_->progress_bar->setValue(0);

    thread_ = new QThread();
}

App::~App()
{
    thread_->quit();
    thread_->wait();
    delete thread_;
    delete ui_;
}

void App::onRipButtonClicked()
{
    QString artist_folder;
    QString album_folder;

    artist_folder = ui_->artist_input->text();
    album_folder = ui_->album_input->text() + " (" + ui_->year_input->text() + ")";

    Worker* worker = new Worker(artist_folder, album_folder);

    QObject::connect(thread_, SIGNAL(started()), worker, SLOT(run()));
    QObject::connect(thread_, SIGNAL(finished()), worker, SLOT(abort()));

    QObject::connect(worker, SIGNAL(sectors(int)), ui_->progress_bar, SLOT(setMaximum(int)));
    QObject::connect(worker, SIGNAL(progress(int)), ui_->progress_bar, SLOT(setValue(int)));

    worker->moveToThread(thread_);
    thread_->start();
}