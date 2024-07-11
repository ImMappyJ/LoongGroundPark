#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSQL();
    initUI();
    initList();
    initMQTT();
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
        "k153zuyAMH6.Loong|securemode=2,signmethod=hmacsha256,timestamp=ttt|",
        "ttt",
        "Loong&k153zuyAMH6",
        "iot-ttt.mqtt.iothub.aliyuncs.com",1883);
    MQTTHandler::conn();
    connect(MQTTHandler::client,SIGNAL(received(QMQTT::Message)),this,SLOT(receive_message_slot(QMQTT::Message)));
    MQTTHandler::subscribe("/k153zuyAMH6/Loong/user/request");
}

void MainWindow::initSQL()
{
    qDebug() << "SQL initing...";
    SQLDB::initdb();
    DataSensor::initdb();
    qDebug() << "Finished";
}

void MainWindow::initList()
{
    this->sensors = new Sensors();
    this->cars = new Cars();
    QList<DataSensor*> datalist = DataSensor::getAll();
    for(DataSensor* sensordata:datalist){
        this->sensors->add_sensor(sensordata->getId(),sensordata->getIsParkSpace());
        qDebug() << "exec";
        this->sensors->set_sensor_nearby(sensordata->getId(),sensordata->getTop(),sensordata->getLeft(),sensordata->getRight(),sensordata->getBottom());
    }
}

int MainWindow::addNewCar()
{

}

void MainWindow::initUI(){
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_time_out()));
    timer->setInterval(1000);
    timer->start(5);
    //timely time show
    QList<DataSensor*> slist = DataSensor::getAll();
    for(DataSensor* data:slist){
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0,QString::number(data->getId()));
        item->setText(1,QString::number(data->getTop()));
        item->setText(2,QString::number(data->getRight()));
        item->setText(3,QString::number(data->getBottom()));
        item->setText(4,QString::number(data->getLeft()));
        item->setText(5,data->getIsParkSpace()?"Yes":"No");
        ui->sensors_treelist->addTopLevelItem(item);
        delete(data);
    }
    //sensors list show
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
    if(DataSensor::clear() == STATUS_ERROR){
        QMessageBox::warning(this,"Warning","Clear failed");
        return;
    }
    for(int i = 0;i < ui->sensors_treelist->topLevelItemCount();i++){
        QTreeWidgetItem* item = ui->sensors_treelist->topLevelItem(i);
        DataSensor* data = new DataSensor(item->text(0).toInt(),item->text(1).toInt(),item->text(4).toInt(),item->text(2).toInt(),item->text(3).toInt(),item->text(5) == "Yes");
        if(DataSensor::add(*data) == STATUS_ERROR){
            QMessageBox::warning(this,"Warning","Failed loaded");
            return;
        }
    }
    QMessageBox::information(this,"Message","Success loaded in sql");
}


void MainWindow::on_sensors_treelist_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->currentID_text->setText(item->text(0));
    ui->topID_text->setText(item->text(1));
    ui->rightID_text->setText(item->text(2));
    ui->bottomID_text->setText(item->text(3));
    ui->leftID_text->setText(item->text(4));
    ui->parkspace_combobox->setCurrentIndex(item->text(5) == "Yes"?0:1);
}

