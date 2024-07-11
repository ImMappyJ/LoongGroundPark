#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Utils/mqtthandler.h"
#include "Utils/timegenerator.h"
#include "Utils/datahandler.h"
#include "Car/Cars.h"
#include "Sensor/Sensors.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QTreeWidgetItem>

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
    void initMQTT();
    void initSQL();
    void initList();
    int addNewCar();
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void receive_message_slot(QMQTT::Message msg);

    void timer_time_out();

    void on_addSensor_button_clicked();

    void on_deleteSensor_button_clicked();

    void on_loadin_button_clicked();

    void on_sensors_treelist_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    Cars* cars;
    Sensors* sensors;
};
#endif // MAINWINDOW_H
