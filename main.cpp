#include <QtCore/QCoreApplication>
#include "File.h"
#include <QString>

#include <QTime>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
#if 0
	std::string filepath = "D:\\WorkSpace\\2k\\";

	std::vector<std::string> vec = GetFiles(filepath);


	QString url = "http://192.168.1.118:10020/face_camera";

	BaseAPI api;

	QTime time;
	time.start();
	std::vector<std::string>::const_iterator it = vec.begin();
	for (it; it != vec.end(); it++)
	{
		std::string fullname = filepath + (*it).c_str();
		QString str = fullname.c_str();
		api.post(url,str);
	}
	qDebug() << "time/ms = " << time.elapsed();


	QString inpath = QString::fromLocal8Bit("D:\\资源文件\\TestDB\\");
	QString outpath = QString::fromLocal8Bit("repeat\\");
	splitRepeatedFile(inpath,outpath);
#endif
	return a.exec();
}
