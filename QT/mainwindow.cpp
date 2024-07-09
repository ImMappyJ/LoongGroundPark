#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Utils/timegenerator.h"
#include <QDebug>
#include <QTimer>

int mode = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MQTTHandler::initMQTT(
        "test.Loong|securemode=2,signmethod=hmacsha256,timestamp=test|",
        "test",
        "test&k153zuyAMH6",
        "test",1883);
    // QString subscription="/sys/k153zuyAMH6/Loong/thing/event/property/post_reply";
    // client->subscribe(subscription);
    MQTTHandler::conn();
    connect(MQTTHandler::client,SIGNAL(received(QMQTT::Message)),this,SLOT(receiveMessageSlot(QMQTT::Message)));
    MQTTHandler::subscribe("/sys/k153zuyAMH6/Loong/thing/event/property/post_reply");
}

void MainWindow::receiveMessageSlot(QMQTT::Message msg){
    qDebug() << "hello";
    qDebug() << msg.payload();
}

void MainWindow::timer_time_out()
{
    ui->time_view->setText("<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">"+get_now_time_str()+"</span></p></body></html>");
}

void MainWindow::initUI(){
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_time_out()));
    timer->setInterval(1000);
    timer->start(5);
}
