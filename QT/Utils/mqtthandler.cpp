#include "Utils/mqtthandler.h"

QMQTT::Client* MQTTHandler::client = nullptr;

void MQTTHandler::receive_message_slot(QMQTT::Message msg)
{
    qDebug() << msg.payload();
}

void MQTTHandler::initMQTT(QString clientID, QByteArray pwd, QString uname, QString connurl,int port)
{
    client = new QMQTT::Client();
    client->setClientId(clientID);
    client->setUsername(uname);
    client->setPassword(pwd);
    client->setHostName(connurl);
    client->setPort(port);
}

int MQTTHandler::conn()
{
    client->connectToHost();
    qDebug() << "Connect";
    QString subscription="/sys/k153zuyAMH6/Loong/thing/event/property/post_reply";
    client->subscribe(subscription);
    return STATUS_OK;
}

int MQTTHandler::subscribe(QString suburl){
    client->subscribe(suburl);
    return STATUS_OK;
}
