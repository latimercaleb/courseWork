#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_objectPositionX_editingFinished();

    void on_objectPositionY_editingFinished();

    void on_objectPositionZ_editingFinished();

    void on_objectRotationX_editingFinished();

    void on_objectRotationY_editingFinished();

    void on_objectRotationZ_editingFinished();

    void on_checkBox_clicked();

    void on_checkBox_released();

    void on_lightPositionX_editingFinished();

    void on_lightPositionY_editingFinished();

    void on_lightPositionZ_editingFinished();

    void on_lightRotationX_editingFinished();

    void on_lightRotationY_editingFinished();

    void on_lightRotationZ_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
