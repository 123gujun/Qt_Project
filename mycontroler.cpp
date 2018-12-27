#include "mycontroler.h"
#include "macrostring.h"
MyControler::MyControler(QObject *parent) : QObject(parent)
{
    QString myurl = URL;

    QString myfilepath = FILEPATH;

    for(int index = 0;index < THREAD_NUM;index++){

        QThread *thr = new QThread;
        MyWorker* worker = new MyWorker(myurl,myfilepath);
        connect(thr, &QThread::finished, worker, &QObject::deleteLater);
        worker->moveToThread(thr);
        connect(thr,SIGNAL(started()),worker,SLOT(post()));
        thr->start();
        vec.push_back(*thr);
    }
}
MyControler::~MyControler()
{
   for(auto&thread:vec){
      if(&thread != nullptr)
          thread.quit();
          thread.wait();
          delete &thread;
   }
}
