/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//! [0]
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
    //setCentralWidget(console);
    ui->widget->addWidget(console);
    ui->widget->setCurrentWidget(console);


//! [1]
    serial = new QSerialPort(this);
    serialTwo = new QSerialPort(this);
//! [1]
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    ui->actionConnect2->setEnabled(true);
    ui->actionDisconnect2->setEnabled(false);


    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serialTwo, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleErrorTwo(QSerialPort::SerialPortError)));

//! [2]
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(serialTwo, SIGNAL(readyRead()), this, SLOT(readDataTwo()));
//! [2]
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
//! [3]
}
//! [3]

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}
//! [4]
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            console->setEnabled(true);
            console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            //ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    serial->close();
    //console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    //ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    console->putData(data);
}
//! [7]

void MainWindow::writeDataTwo(const QByteArray &data){
    serialTwo->write(data);
}

void MainWindow::readDataTwo(){
    QByteArray data = serialTwo->readAll();
    console->putData(data);
}

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::handleErrorTwo(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serialTwo->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::on_pushButton_clicked()
{
    QByteArray mess;
    mess.insert(0,ui->lineEdit->text());
    writeData(mess);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label->setText(QString::number(position));
}

void MainWindow::on_pushButton_2_clicked()
{
    static bool state = false;
    QByteArray A = QByteArray("a");
    if(state)
    {
        ui->pushButton_2->setText("Use Slider Input");
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->horizontalSlider_3->setEnabled(false);
        state = false;
        A[0] = 100;
    }
    else
    {
        ui->pushButton_2->setText("Use Sensor Input");
        ui->horizontalSlider->setEnabled(true);
        ui->horizontalSlider_2->setEnabled(true);
        ui->horizontalSlider_3->setEnabled(true);
        state = true;
        A[0] = 101;
    }

    writeData(A);
    //ui->lineEdit->setText(QString::number(A[0]));
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    ui->label_2->setText(QString::number(position));
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    //update primary variable
    QByteArray A = QByteArray("ab");
    A[0] = 30;
    A[1] = ui->horizontalSlider->value();
    writeData(A);
    //ui->lineEdit->setText(QString::number(A[1]));
}

void MainWindow::on_pushButton_3_clicked()
{
    //switch servo direction


}

void MainWindow::on_horizontalSlider_2_sliderReleased()
{
    //update secondary variable
    QByteArray A = QByteArray("ab");
    A[0] = 80;
    A[1] = ui->horizontalSlider_2->value();
    writeData(A);
    //ui->lineEdit->setText(QString::number(A[1]));
}

void MainWindow::on_actionConnect2_triggered()
{
    SettingsDialog::Settings p = settings->settings();
    serialTwo->setPortName(p.name);
    serialTwo->setBaudRate(p.baudRate);
    serialTwo->setDataBits(p.dataBits);
    serialTwo->setParity(p.parity);
    serialTwo->setStopBits(p.stopBits);
    serialTwo->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            console->setEnabled(true);
            console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect2->setEnabled(false);
            ui->actionDisconnect2->setEnabled(true);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }

}

void MainWindow::on_actionDisconnect2_triggered()
{
    serialTwo->close();
    //console->setEnabled(false);
    ui->actionConnect2->setEnabled(true);
    ui->actionDisconnect2->setEnabled(false);
    //ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    ui->label_3->setText(QString::number(position));
}

void MainWindow::on_horizontalSlider_3_sliderReleased()
{
    //update third variable
    QByteArray A = QByteArray("ab");
    A[0] = 90;
    A[1] = ui->horizontalSlider_3->value();
    writeData(A);
}
