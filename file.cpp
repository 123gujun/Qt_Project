#include "File.h"
#include <QDir>
#include<QStringList>
#include<qDebug>
#include <QBuffer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCryptographicHash> 
#include <QVector>
#include <QFile>
#include <QTextCodec>


//get files from the current directory
QVector<QString> GetFiles(QString filepath)
{
	QDir dir(filepath);

	if (!dir.exists())
		qDebug() << "file path is not exist";
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	QStringList list = dir.entryList();

	QStringList::const_iterator iterator = list.begin();
	QVector<QString> vec;
	while (iterator != list.end()) {
		QFileInfo fileInfo(filepath + (*iterator));
		QString suffix = fileInfo.suffix();
		if (suffix.toLower() == "png" || suffix.toLower() == "jpg")
			vec.push_back(QString::fromLocal8Bit((*iterator).toLocal8Bit().constData()));
		iterator++;
	}
	return vec;
}
QString getMD5(QString fileNamePath)
{
	QFile theFile(fileNamePath);
	theFile.open(QIODevice::ReadOnly);
	QByteArray ba = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
	theFile.close();
	return QString(ba.toHex().constData());
}

void splitRepeatedFile(QString filepath, QString outFilePath)
{
	//outFilePath.replace("\\", "/");
	QVector<QString> fileVec = GetFiles(filepath);

	QDir dir(filepath);

	QVector<QString> md5Vec;
	for (QString & str : fileVec) {
		//get md5
		QString md5 = getMD5(filepath + str);

		if (md5Vec.contains(md5) == false) {

			md5Vec.push_back(md5);
		}
		else {
			//move repeat files to other directory
			QString file = QString::fromLocal8Bit(str.toLocal8Bit().data());

			QDir outDir(filepath + outFilePath);
			if (!outDir.exists()) {
				dir.mkdir(outFilePath);
			}
			if (true == QFile::copy(filepath + file, filepath + outFilePath + file)) {
				qDebug() << QString::fromLocal8Bit("repeat文件") << file;
				dir.remove(file);
			}
		}
	}


}


void splitDir(QString filepath)
{
	QVector<QString> fileVec = GetFiles(filepath);
	QDir dir(filepath);
	for (int i = 0; i < fileVec.size(); i++) {

		if (i < fileVec.size() / 2) {

			//construct different dir
			QString outpath = "forward";
			dir = QDir(filepath + outpath);
			if (!dir.exists()) {
				dir.mkdir(outpath);
			}
		}
		else {
			//construct different dir
			QString outpath = "afterward";
			dir = QDir(filepath + outpath);
			if (!dir.exists()) {
				dir.mkdir(outpath);
			}
		}
		if (true == QFile::copy(filepath + fileVec[i], dir.dirName() + fileVec[i])) {
			qDebug() << QString::fromLocal8Bit("文件名称") << fileVec[i];
		}

	}
}



//图片文件转utf-8格式的文件
QByteArray Image_To_utf8(QString ImgPath)
{
	QFile file(ImgPath);
	if (!file.open(QIODevice::ReadOnly) || file.size() == 0)
	{
		file.close();
		return NULL;
	}
	QByteArray fdata = file.readAll();
	if (fdata.isEmpty()) {
		return NULL;
	}
	file.close();

	return fdata.toBase64();
}


BaseAPI::BaseAPI()
{
	httpRequest.setRawHeader("Content-Type", "application/json");
	httpRequest.setRawHeader("Accept-Encoding", "gzip, deflate");
	httpRequest.setRawHeader("Accept", "*/*");

	//QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

BaseAPI::~BaseAPI()
{
	networkAccessManager.disconnect();
	if (settings) {
		delete settings;
		settings = nullptr;
	}
}

void BaseAPI::get(const QString url)
{
	httpRequest.setUrl(QUrl(url));
	networkAccessManager.get(httpRequest);
}

void BaseAPI::post(const QString url, const QByteArray &data)
{
	httpRequest.setUrl(QUrl(url));
	networkAccessManager.post(httpRequest, data);
}
void BaseAPI::post(const QString url, QString &filename)
{
	QString imageStr = Image_To_utf8(filename);

	QByteArray tmp = Image_To_utf8(filename);
	QJsonValue value(imageStr);

	QJsonArray arr;
	arr.append(value);

	QJsonDocument  doc;
	doc.setArray(arr);
	QByteArray bte = doc.toJson(QJsonDocument::Compact);

	httpRequest.setUrl(url);

	QByteArray  array("{\"time\":1515151515,\"cid\":\"290200001264\",\"faces\":");

	array.append(QString(bte.data()) + "," + "\"image\":\"" + tmp.data() + "\"}");

	httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));


	networkAccessManager.post(httpRequest, array);
}

void BaseAPI::postTohawkEye(const QString url, QString &filename)
{

	QString imageStr = Image_To_utf8(filename);

	QByteArray tmp = Image_To_utf8(filename);
	QJsonValue value(imageStr);

	QJsonArray arr;
	arr.append(value);

	QJsonDocument  doc;
	doc.setArray(arr);
	QByteArray bte = doc.toJson(QJsonDocument::Compact);

	httpRequest.setUrl(url);

	QByteArray  array("{\"time\":1515151515,\"cid\":\"290200001264\",\"faces\":");

	array.append(QString(bte.data()) + "," + "\"image\":\"" + tmp.data() + "\"}");

	httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));


	networkAccessManager.post(httpRequest, array);


}

void BaseAPI::serviceRequestFinished(QNetworkReply *reply)
{
	QString str = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

	std::cout << "BaseAPI...serviceRequestFinished...statusCode:" << str.toStdString().c_str() << std::endl;

	if (reply->error() == QNetworkReply::NoError) {
		requestFinished(reply, reply->readAll(), 0);
	}
	else {
		requestFinished(reply, "", 0);
	}
	reply->deleteLater();
}

void BaseAPI::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
{
	std::cout << "网络ok " << data.toStdString().c_str() << std::endl;
}