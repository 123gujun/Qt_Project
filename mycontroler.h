#ifndef MYCONTROLER_H
#define MYCONTROLER_H

#include <QObject>
#include "myworker.h"
#include<QThread>
#include<QVector>


class MyControler : public QObject
{
    Q_OBJECT
public:
    explicit MyControler(QObject *parent = nullptr);
    ~MyControler();

signals:

public slots:
private:
    QVector<QThread> vec;
};

#endif // MYCONTROLER_H
