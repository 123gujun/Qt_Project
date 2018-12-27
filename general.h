#ifndef GENERAL_H
#define GENERAL_H
#include<QByteArray>
#include<QString>
#include<QVector>
//常用的公共文件

//图片转为base64
QByteArray Image_To_Base64(QString ImgPath);

//从指定的路径获取图片文件列表
QVector<QString> GetFiles(QString filepath);

#endif // GENERAL_H
