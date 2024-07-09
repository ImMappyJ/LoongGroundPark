#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H
#include "mqtt/qmqtt.h"
#include "MacroDefine.h"
#include <QString>
#include <QByteArray>
#include <QHostAddress>
#include <QDebug>
#include <QMetaObject>


class MQTTHandler{
private:
public:
    static QMQTT::Client* client;
    static void initMQTT(QString clientID,QByteArray pwd,QString uname,QString connurl,int port);
    static int conn();
    static int subscribe(QString suburl);
};


#endif // MQTTHANDLER_H
