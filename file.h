#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QString>
#include <QImage>




QVector<QString> GetFiles(QString filepath);

QByteArray Image_To_utf8(QString ImgPath);

//get md5 value
QString getMD5(QString filepath);

// filepath  /*in*/
// outFile   /*out*/
void splitRepeatedFile(QString filepath,QString outFile);

//二分文件夹

void splitDir(QString path/*in*/);
class BaseAPI :public QObject
{
	Q_OBJECT

public:
	BaseAPI();
	~BaseAPI();
	void get(const QString url);
	void post(const QString url, const QByteArray &data);

	void post(const QString url, QString &filename);


	void postTohawkEye(const QString url, QString &filename);

protected:
	virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode);	

public slots:
	void serviceRequestFinished(QNetworkReply *reply);

private:
	QNetworkRequest httpRequest;
	QNetworkAccessManager networkAccessManager;
	QSettings *settings;

};

