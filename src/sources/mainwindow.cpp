/*
 Copyright 2012 Joseph W. Dougherty

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTrayIcon();

     connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
             SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->windowIcon());
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    show();
    trayIcon->hide();
}

void MainWindow::changeEvent(QEvent *e ){
    switch (e->type()){
        case QEvent::WindowStateChange:
            if (this->windowState() & Qt::WindowMinimized){
                hide();
                trayIcon->show();
            }
            break;

        default:
            break;
    }

    QMainWindow::changeEvent(e);
}
