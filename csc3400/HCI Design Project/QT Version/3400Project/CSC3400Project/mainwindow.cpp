#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "glwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /* connect(ui->GlWindow, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
    connect(ui->GlWindow, SIGNAL(yRotationChanged(int)), ui->rotYSlider, SLOT(setValue(int)));
    connect(ui->GlWindow, SIGNAL(zRotationChanged(int)), ui->rotZSlider, SLOT(setValue(int)));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_objectPositionX_editingFinished()
{
    //change x position

}

void MainWindow::on_objectPositionY_editingFinished()
{
    //change y position
}

void MainWindow::on_objectPositionZ_editingFinished()
{
    //change z position
}



void MainWindow::on_objectRotationX_editingFinished()
{
    //change x rotation
}

void MainWindow::on_objectRotationY_editingFinished()
{
    // change y rotation
}

void MainWindow::on_objectRotationZ_editingFinished()
{
    //change z rotation
}

void MainWindow::on_checkBox_clicked()
{
    //call light source constructor
    //set bool lightOn = true;
}

void MainWindow::on_checkBox_released()
{
    //call light source destructor
}

void MainWindow::on_lightPositionX_editingFinished()
{
    //if lightOn==true
    //set light position x
}

void MainWindow::on_lightPositionY_editingFinished()
{
    //if lightOn==true
    //set light position y

}

void MainWindow::on_lightPositionZ_editingFinished()
{
    //if lightOn==true
    //set light position z

}

void MainWindow::on_lightRotationX_editingFinished()
{
    //if lightOn==true
    //set light rotation x

}

void MainWindow::on_lightRotationY_editingFinished()
{
    //if lightOn==true
    //set light rotation y

}

void MainWindow::on_lightRotationZ_editingFinished()
{
    //if lightOn==true
    //set light rotation z

}
