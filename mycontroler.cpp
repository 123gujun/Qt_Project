#include "mycontroler.h"
#include "macrostring.h"
#include "myworker.h"

QVector<QString>::iterator it = MyWorker::m_fileVec.begin();

MyControler::MyControler(QObject *parent):QThread (parent)
{

}
MyControler::~MyControler()
{

}


void MyControler::run()
{
 MyWorker worker(QString(URL),QString(FILEPATH),nullptr);
 while (true) {
     if(it != MyWorker::m_fileVec.end())
      {
             //dealwith
          mutex.lock();
          worker.post(*it);
          it++;
          mutex.unlock();
      }else
     {
         return;
     }
 }
}
