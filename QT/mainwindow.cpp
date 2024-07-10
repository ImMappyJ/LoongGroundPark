#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    initMQTT();
    initSQL();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    initMQTT();
}

void MainWindow::receive_message_slot(QMQTT::Message msg){
    qDebug() << msg.payload();
}

void MainWindow::timer_time_out()
{
    ui->time_view->setText("<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">"+get_now_time_str()+"</span></p></body></html>");
}

void MainWindow::initMQTT(){
    MQTTHandler::initMQTT(
        "t.Loong|securemode=2,signmethod=hmacsha256,timestamp=t|",
        "t",
        "Loong&t",
        "iot-t.mqtt.iothub.aliyuncs.com",1883);
    MQTTHandler::conn();
    connect(MQTTHandler::client,SIGNAL(received(QMQTT::Message)),this,SLOT(receive_message_slot(QMQTT::Message)));
    MQTTHandler::subscribe("/t/Loong/user/request");
}

void MainWindow::initSQL()
{
}

void MainWindow::initUI(){
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_time_out()));
    timer->setInterval(1000);
    timer->start(5);
}

void MainWindow::on_addSensor_button_clicked()
{
    QString currentID = ui->currentID_text->toPlainText();
    QString leftID = ui->leftID_text->toPlainText();
    QString rightID = ui->rightID_text->toPlainText();
    QString topID = ui->topID_text->toPlainText();
    QString bottomID = ui->bottomID_text->toPlainText();
    QString parkSpace = ui->parkspace_combobox->itemText(ui->parkspace_combobox->currentIndex());
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,currentID);
    item->setText(1,topID);
    item->setText(2,rightID);
    item->setText(3,bottomID);
    item->setText(4,leftID);
    item->setText(5,parkSpace);
    ui->sensors_treelist->insertTopLevelItem(0,item);
}


void MainWindow::on_deleteSensor_button_clicked()
{
    QList<QTreeWidgetItem*> current_selected_indexes = ui->sensors_treelist->selectedItems();
    foreach(QTreeWidgetItem* selected_index,current_selected_indexes){
        int index = ui->sensors_treelist->indexOfTopLevelItem(selected_index);
        ui->sensors_treelist->takeTopLevelItem(index);
    }
}


void MainWindow::on_loadin_button_clicked()
{
    DataSensor* data = new DataSensor(1,2,3,4,5,false);
}

