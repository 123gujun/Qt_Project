#include "myworker.h"
#include "general.h"
#include "macrostring.h"
#include<QJsonValue>
#include<QJsonArray>
#include<QJsonDocument>
QMutex mutex;

QVector<QString>MyWorker::m_fileVec = GetFiles(QString(FILEPATH));

MyWorker::MyWorker(QString&url,QString& filepath,QObject *parent):\
 m_url(url),m_filepath(filepath),QObject(parent)
{
    httpRequest.setRawHeader("Content-Type", "application/json");
    httpRequest.setRawHeader("Accept-Encoding", "gzip, deflate");
    httpRequest.setRawHeader("Accept", "*/*");
}
void MyWorker::post()
{
    httpRequest.setUrl(m_url);
    for(auto&filename:m_fileVec)
    {
        mutex.lock();
        QByteArray array = GetJsonString(QString(FILEPATH) + filename);
        networkAccessManager.post(httpRequest,array);
        m_fileVec.removeOne(filename);
        mutex.unlock();
    }
}
void MyWorker::get()
{

}
QByteArray MyWorker::GetJsonString(QString fullname)
{
    QString imageStr = Image_To_Base64(fullname);

    QByteArray tmp  = Image_To_Base64(fullname);
    QJsonValue value(imageStr);

    QJsonArray arr;
    arr.append(value);

    QJsonDocument  doc;
    doc.setArray(arr);
    QByteArray bte = doc.toJson(QJsonDocument::Compact);

    QByteArray  array("{\"time\":1516002690,\"cid\":\"290200001263\",\"faces\":");

    array.append(QString(bte.data()) + "," + "\"image\":\"" + tmp.data() + "\"}");

    return array;
}
MyWorker::~MyWorker()
{

}
