/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *displayWidget;
    QSpinBox *redSpinBox;
    QSpinBox *greenSpinBox;
    QSpinBox *blueSpinBox;
    QCheckBox *cb1;
    QCheckBox *cb2;
    QPushButton *accept;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1011, 411);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        redSlider = new QSlider(centralWidget);
        redSlider->setObjectName(QStringLiteral("redSlider"));
        redSlider->setGeometry(QRect(730, 10, 111, 16));
        redSlider->setMaximum(255);
        redSlider->setOrientation(Qt::Horizontal);
        greenSlider = new QSlider(centralWidget);
        greenSlider->setObjectName(QStringLiteral("greenSlider"));
        greenSlider->setGeometry(QRect(730, 50, 111, 20));
        greenSlider->setMaximum(255);
        greenSlider->setOrientation(Qt::Horizontal);
        blueSlider = new QSlider(centralWidget);
        blueSlider->setObjectName(QStringLiteral("blueSlider"));
        blueSlider->setGeometry(QRect(730, 90, 111, 20));
        blueSlider->setMaximum(255);
        blueSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(710, 10, 15, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(710, 50, 15, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(710, 90, 15, 17));
        displayWidget = new QWidget(centralWidget);
        displayWidget->setObjectName(QStringLiteral("displayWidget"));
        displayWidget->setGeometry(QRect(890, 0, 91, 101));
        displayWidget->setAutoFillBackground(true);
        redSpinBox = new QSpinBox(centralWidget);
        redSpinBox->setObjectName(QStringLiteral("redSpinBox"));
        redSpinBox->setGeometry(QRect(840, 0, 48, 26));
        redSpinBox->setMaximum(255);
        greenSpinBox = new QSpinBox(centralWidget);
        greenSpinBox->setObjectName(QStringLiteral("greenSpinBox"));
        greenSpinBox->setGeometry(QRect(840, 40, 48, 26));
        greenSpinBox->setMaximum(255);
        blueSpinBox = new QSpinBox(centralWidget);
        blueSpinBox->setObjectName(QStringLiteral("blueSpinBox"));
        blueSpinBox->setGeometry(QRect(840, 80, 48, 26));
        blueSpinBox->setMaximum(255);
        cb1 = new QCheckBox(centralWidget);
        cb1->setObjectName(QStringLiteral("cb1"));
        cb1->setGeometry(QRect(800, 140, 121, 23));
        cb2 = new QCheckBox(centralWidget);
        cb2->setObjectName(QStringLiteral("cb2"));
        cb2->setGeometry(QRect(800, 190, 121, 23));
        accept = new QPushButton(centralWidget);
        accept->setObjectName(QStringLiteral("accept"));
        accept->setGeometry(QRect(760, 230, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1011, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(redSlider, SIGNAL(valueChanged(int)), redSpinBox, SLOT(setValue(int)));
        QObject::connect(redSpinBox, SIGNAL(valueChanged(int)), redSlider, SLOT(setValue(int)));
        QObject::connect(greenSlider, SIGNAL(valueChanged(int)), greenSpinBox, SLOT(setValue(int)));
        QObject::connect(greenSpinBox, SIGNAL(valueChanged(int)), greenSlider, SLOT(setValue(int)));
        QObject::connect(blueSlider, SIGNAL(valueChanged(int)), blueSpinBox, SLOT(setValue(int)));
        QObject::connect(blueSpinBox, SIGNAL(valueChanged(int)), blueSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "R", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "G", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "B", nullptr));
        cb1->setText(QApplication::translate("MainWindow", "Zmie\305\204 Kolor 1", nullptr));
        cb2->setText(QApplication::translate("MainWindow", "Zmie\305\204 Kolor 2", nullptr));
        accept->setText(QApplication::translate("MainWindow", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
