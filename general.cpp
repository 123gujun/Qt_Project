#include "general.h"
#include<QFile>
#include<QDir>
#include<QDebug>
#include<QFileInfo>

QByteArray Image_To_Base64(QString ImgPath)
{
    QFile file(ImgPath);
    if (!file.open(QIODevice::ReadOnly) || file.size() == 0)
    {
        file.close();
        return nullptr;
    }
    QByteArray fdata = file.readAll();
    if (fdata.isEmpty()) {
        return nullptr;
    }
    file.close();
    return fdata.toBase64();
}

QVector<QString> GetFiles(QString & filepath)
{
   QDir dir(filepath);
   if (! dir.exists())
       qDebug() << "file path is not exist";
   dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
   QStringList list = dir.entryList();

   QStringList::const_iterator iterator = list.begin();

   QVector<QString> vec;
   while (iterator != list.end()) {
       QFileInfo fileInfo(filepath + (*iterator));
       QString suffix = fileInfo.suffix();
       if(suffix == "png" || suffix == "jpg")
           vec.push_back((*iterator).toLocal8Bit().constData());
       iterator++;
   }
   return vec;
}
