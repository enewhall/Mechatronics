/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionQuit;
    QAction *actionConnect2;
    QAction *actionDisconnect2;
    QWidget *centralWidget;
    QStackedWidget *widget;
    QWidget *page;
    QWidget *page_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QSlider *horizontalSlider;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSlider *horizontalSlider_3;
    QLabel *label_3;
    QSlider *horizontalSlider_4;
    QLabel *label_4;
    QSpinBox *spinBox;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(835, 454);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        actionConnect2 = new QAction(MainWindow);
        actionConnect2->setObjectName(QStringLiteral("actionConnect2"));
        actionConnect2->setIcon(icon);
        actionDisconnect2 = new QAction(MainWindow);
        actionDisconnect2->setObjectName(QStringLiteral("actionDisconnect2"));
        actionDisconnect2->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QStackedWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 210, 821, 161));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        widget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        widget->addWidget(page_2);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 60, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 60, 191, 20));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setEnabled(false);
        horizontalSlider->setGeometry(QRect(370, 60, 160, 22));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 30, 111, 16));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(410, 100, 111, 23));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(570, 100, 171, 23));
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setEnabled(false);
        horizontalSlider_3->setGeometry(QRect(10, 130, 160, 22));
        horizontalSlider_3->setMaximum(2);
        horizontalSlider_3->setValue(1);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 100, 121, 16));
        horizontalSlider_4 = new QSlider(centralWidget);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setEnabled(false);
        horizontalSlider_4->setGeometry(QRect(200, 130, 160, 22));
        horizontalSlider_4->setMaximum(255);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 100, 101, 16));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(220, 30, 42, 22));
        spinBox->setMaximum(9);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 835, 21));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuCalls->addAction(actionConnect);
        menuCalls->addAction(actionDisconnect);
        menuCalls->addSeparator();
        menuCalls->addAction(actionQuit);
        menuTools->addAction(actionConfigure);
        menuTools->addAction(actionClear);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAboutQt);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addAction(actionClear);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionConnect2);
        mainToolBar->addAction(actionDisconnect2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Motor lab Reader", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About program", 0));
#endif // QT_NO_TOOLTIP
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Alt+A", 0));
        actionAboutQt->setText(QApplication::translate("MainWindow", "About Qt", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "C&onnect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to serial port", 0));
#endif // QT_NO_TOOLTIP
        actionConnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect from serial port", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionConfigure->setText(QApplication::translate("MainWindow", "&Configure", 0));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure serial port", 0));
#endif // QT_NO_TOOLTIP
        actionConfigure->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0));
        actionClear->setText(QApplication::translate("MainWindow", "C&lear", 0));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("MainWindow", "Clear data", 0));
#endif // QT_NO_TOOLTIP
        actionClear->setShortcut(QApplication::translate("MainWindow", "Alt+L", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionConnect2->setText(QApplication::translate("MainWindow", "Connect2", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect2->setToolTip(QApplication::translate("MainWindow", "Connect serial port 2", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect2->setText(QApplication::translate("MainWindow", "Disconnect2", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect2->setToolTip(QApplication::translate("MainWindow", "Disconnect serial port 2", 0));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("MainWindow", "Test", 0));
        lineEdit->setText(QString());
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QApplication::translate("MainWindow", "Input for primary", 0));
#endif // QT_NO_STATUSTIP
        label->setText(QApplication::translate("MainWindow", "Stepper Motor Slider", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Use Slider Input", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Electromagnet ON/OFF", 0));
        label_3->setText(QApplication::translate("MainWindow", "DC MOTOR SLIDER", 0));
        label_4->setText(QApplication::translate("MainWindow", "Servo Motor Slider", 0));
#ifndef QT_NO_STATUSTIP
        spinBox->setStatusTip(QApplication::translate("MainWindow", "The xth motor of that type", 0));
#endif // QT_NO_STATUSTIP
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
