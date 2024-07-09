QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Car/CarStatus.cpp \
    Car/Cars.cpp \
    Sensor/SensorStatus.cpp \
    Sensor/Sensors.cpp \
    Utils/datahandler.cpp \
    Utils/mqtthandler.cpp \
    Utils/timegenerator.cpp \
    main.cpp \
    mainwindow.cpp \
    mqtt/qmqtt_client.cpp \
    mqtt/qmqtt_client_p.cpp \
    mqtt/qmqtt_frame.cpp \
    mqtt/qmqtt_message.cpp \
    mqtt/qmqtt_network.cpp \
    mqtt/qmqtt_router.cpp \
    mqtt/qmqtt_routesubscription.cpp \
    mqtt/qmqtt_socket.cpp \
    mqtt/qmqtt_ssl_socket.cpp \
    mqtt/qmqtt_timer.cpp \
    mqtt/qmqtt_websocket.cpp \
    mqtt/qmqtt_websocketiodevice.cpp

HEADERS += \
    Car/CarStatus.h \
    Car/Cars.h \
    MacroDefine.h \
    Sensor/SensorStatus.h \
    Sensor/Sensors.h \
    Utils/datahandler.h \
    Utils/mqtthandler.h \
    Utils/timegenerator.h \
    mainwindow.h \
    mqtt/qmqtt.h \
    mqtt/qmqtt_client.h \
    mqtt/qmqtt_client_p.h \
    mqtt/qmqtt_frame.h \
    mqtt/qmqtt_global.h \
    mqtt/qmqtt_message.h \
    mqtt/qmqtt_message_p.h \
    mqtt/qmqtt_network_p.h \
    mqtt/qmqtt_networkinterface.h \
    mqtt/qmqtt_routedmessage.h \
    mqtt/qmqtt_router.h \
    mqtt/qmqtt_routesubscription.h \
    mqtt/qmqtt_socket_p.h \
    mqtt/qmqtt_socketinterface.h \
    mqtt/qmqtt_ssl_socket_p.h \
    mqtt/qmqtt_timer_p.h \
    mqtt/qmqtt_timerinterface.h \
    mqtt/qmqtt_websocket_p.h \
    mqtt/qmqtt_websocketiodevice_p.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    LoongLinuxManager_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qmqtt-master/build/Desktop_Qt_5_15_2_GCC_64bit-Release/lib/release/ -lQt5Qmqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qmqtt-master/build/Desktop_Qt_5_15_2_GCC_64bit-Release/lib/debug/ -lQt5Qmqtt

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''

RESOURCES += \
    resource.qrc

SUBDIRS += \
    mqtt/qmqtt.pro

DISTFILES += \
    mqtt/qmqtt.pri \
    mqtt/qmqtt.qbs
