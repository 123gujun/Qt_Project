#ifndef MYCONTROLER_H
#define MYCONTROLER_H

#include <QThread>
#include "myworker.h"
#include<QThread>
#include<QVector>


class MyControler : public QThread
{
    Q_OBJECT
public:
    explicit MyControler(QObject *parent = nullptr);
    ~MyControler();

protected:
    virtual void run();

signals:

public slots:
private:

};

#endif // MYCONTROLER_H
