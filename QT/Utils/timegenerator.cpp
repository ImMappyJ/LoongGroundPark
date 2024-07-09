#include "timegenerator.h"

long get_now_time() {
    time_t tt;
    time(&tt);
    struct tm time_struct;
    localtime_r(&tt, &time_struct); // 使用localtime_r替代localtime_s
    return mktime(&time_struct);
}

QString get_now_time_str()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    return formattedTime;
}
