#include <QCoreApplication>
#include <QDebug>
#include "mycontroler.h"
#include<QTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime time;
    time.start();


    qDebug() << QObject::tr("发送数据使用的时间=") << time.elapsed()/1000<<"s";
    return a.exec();
}
