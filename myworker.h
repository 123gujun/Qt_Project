#ifndef MYWORKER_H
#define MYWORKER_H

#include<QObject>
#include<QString>
#include<QNetworkRequest>
#include<QNetworkAccessManager>
#include<QByteArray>
#include<QVector>

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QString url,QString filepath,QObject *parent = nullptr);

    //发送post请求
    void post(QString & filename);
    //发送get请求
    void get();
    //销毁资源
    ~MyWorker();
private:
    QByteArray GetJsonString(QString fullname);
signals:

public slots:
public:
    static QVector<QString> m_fileVec;
private:
    QString m_url;
    QString m_filepath;
    QNetworkRequest httpRequest;
    QNetworkAccessManager networkAccessManager;

};

#endif // MYWORKER_H
