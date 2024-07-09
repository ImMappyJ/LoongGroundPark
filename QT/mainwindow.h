#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Utils/mqtthandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void initUI();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void receiveMessageSlot(QMQTT::Message msg);
    void timer_time_out();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
