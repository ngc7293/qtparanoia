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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_App
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *rip_button;
    QProgressBar *progress_bar;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *artist_input;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *album_input;
    QLabel *label;
    QSpinBox *year_input;
    QListView *track_list;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *App)
    {
        if (App->objectName().isEmpty())
            App->setObjectName(QStringLiteral("App"));
        App->resize(525, 275);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(App->sizePolicy().hasHeightForWidth());
        App->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(App);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        rip_button = new QPushButton(centralwidget);
        rip_button->setObjectName(QStringLiteral("rip_button"));

        horizontalLayout_3->addWidget(rip_button);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        progress_bar = new QProgressBar(centralwidget);
        progress_bar->setObjectName(QStringLiteral("progress_bar"));
        progress_bar->setValue(0);

        gridLayout->addWidget(progress_bar, 4, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(50, 0));

        horizontalLayout_2->addWidget(label_2);

        artist_input = new QLineEdit(centralwidget);
        artist_input->setObjectName(QStringLiteral("artist_input"));
        artist_input->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(artist_input);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(label_3);

        album_input = new QLineEdit(centralwidget);
        album_input->setObjectName(QStringLiteral("album_input"));
        album_input->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(album_input);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        year_input = new QSpinBox(centralwidget);
        year_input->setObjectName(QStringLiteral("year_input"));
        year_input->setMinimumSize(QSize(65, 25));

        horizontalLayout->addWidget(year_input);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        track_list = new QListView(centralwidget);
        track_list->setObjectName(QStringLiteral("track_list"));

        gridLayout->addWidget(track_list, 3, 0, 1, 1);

        App->setCentralWidget(centralwidget);
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
        label_2->setText(QApplication::translate("App", "Artist", Q_NULLPTR));
        label_3->setText(QApplication::translate("App", "Album", Q_NULLPTR));
        label->setText(QApplication::translate("App", "Year", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class App: public Ui_App {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
