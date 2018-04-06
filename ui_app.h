/********************************************************************************
** Form generated from reading UI file 'app.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_H
#define UI_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_App
{
public:
    QWidget *central_widget;
    QGridLayout *gridLayout;
    QVBoxLayout *vbox_1;
    QHBoxLayout *hbox_1;
    QComboBox *device_dropdown;
    QPushButton *rip_button;
    QPushButton *abort_button;
    QHBoxLayout *hbox_2;
    QLabel *artist_label;
    QLineEdit *artist_input;
    QHBoxLayout *hbox_3;
    QLabel *album_label;
    QLineEdit *album_input;
    QLabel *year_label;
    QSpinBox *year_input;
    QTableView *tag_table;
    QProgressBar *progress_bar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *App)
    {
        if (App->objectName().isEmpty())
            App->setObjectName(QStringLiteral("App"));
        App->resize(525, 387);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(App->sizePolicy().hasHeightForWidth());
        App->setSizePolicy(sizePolicy);
        central_widget = new QWidget(App);
        central_widget->setObjectName(QStringLiteral("central_widget"));
        gridLayout = new QGridLayout(central_widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        vbox_1 = new QVBoxLayout();
        vbox_1->setObjectName(QStringLiteral("vbox_1"));
        vbox_1->setSizeConstraint(QLayout::SetMaximumSize);
        hbox_1 = new QHBoxLayout();
        hbox_1->setObjectName(QStringLiteral("hbox_1"));
        device_dropdown = new QComboBox(central_widget);
        device_dropdown->setObjectName(QStringLiteral("device_dropdown"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(device_dropdown->sizePolicy().hasHeightForWidth());
        device_dropdown->setSizePolicy(sizePolicy1);

        hbox_1->addWidget(device_dropdown);

        rip_button = new QPushButton(central_widget);
        rip_button->setObjectName(QStringLiteral("rip_button"));

        hbox_1->addWidget(rip_button);

        abort_button = new QPushButton(central_widget);
        abort_button->setObjectName(QStringLiteral("abort_button"));

        hbox_1->addWidget(abort_button);


        vbox_1->addLayout(hbox_1);

        hbox_2 = new QHBoxLayout();
        hbox_2->setObjectName(QStringLiteral("hbox_2"));
        artist_label = new QLabel(central_widget);
        artist_label->setObjectName(QStringLiteral("artist_label"));
        artist_label->setMinimumSize(QSize(45, 0));

        hbox_2->addWidget(artist_label);

        artist_input = new QLineEdit(central_widget);
        artist_input->setObjectName(QStringLiteral("artist_input"));

        hbox_2->addWidget(artist_input);


        vbox_1->addLayout(hbox_2);

        hbox_3 = new QHBoxLayout();
        hbox_3->setObjectName(QStringLiteral("hbox_3"));
        album_label = new QLabel(central_widget);
        album_label->setObjectName(QStringLiteral("album_label"));
        album_label->setMinimumSize(QSize(45, 0));

        hbox_3->addWidget(album_label);

        album_input = new QLineEdit(central_widget);
        album_input->setObjectName(QStringLiteral("album_input"));

        hbox_3->addWidget(album_input);

        year_label = new QLabel(central_widget);
        year_label->setObjectName(QStringLiteral("year_label"));

        hbox_3->addWidget(year_label);

        year_input = new QSpinBox(central_widget);
        year_input->setObjectName(QStringLiteral("year_input"));
        year_input->setMinimum(-3000);
        year_input->setMaximum(3000);

        hbox_3->addWidget(year_input);


        vbox_1->addLayout(hbox_3);

        tag_table = new QTableView(central_widget);
        tag_table->setObjectName(QStringLiteral("tag_table"));
        tag_table->setShowGrid(false);
        tag_table->setGridStyle(Qt::SolidLine);
        tag_table->horizontalHeader()->setCascadingSectionResizes(true);
        tag_table->horizontalHeader()->setStretchLastSection(true);
        tag_table->verticalHeader()->setVisible(true);
        tag_table->verticalHeader()->setDefaultSectionSize(21);
        tag_table->verticalHeader()->setStretchLastSection(false);

        vbox_1->addWidget(tag_table);

        progress_bar = new QProgressBar(central_widget);
        progress_bar->setObjectName(QStringLiteral("progress_bar"));
        progress_bar->setMaximum(1);
        progress_bar->setValue(0);

        vbox_1->addWidget(progress_bar);


        gridLayout->addLayout(vbox_1, 1, 0, 1, 1);

        App->setCentralWidget(central_widget);
        menubar = new QMenuBar(App);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 525, 22));
        App->setMenuBar(menubar);
        statusbar = new QStatusBar(App);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        App->setStatusBar(statusbar);

        retranslateUi(App);

        QMetaObject::connectSlotsByName(App);
    } // setupUi

    void retranslateUi(QMainWindow *App)
    {
        App->setWindowTitle(QApplication::translate("App", "QtParanoia", Q_NULLPTR));
        rip_button->setText(QApplication::translate("App", "Rip", Q_NULLPTR));
        abort_button->setText(QApplication::translate("App", "Abort", Q_NULLPTR));
        artist_label->setText(QApplication::translate("App", "Artist", Q_NULLPTR));
        album_label->setText(QApplication::translate("App", "Album", Q_NULLPTR));
        year_label->setText(QApplication::translate("App", "Year", Q_NULLPTR));
        progress_bar->setFormat(QApplication::translate("App", "%v/%m", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class App: public Ui_App {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
