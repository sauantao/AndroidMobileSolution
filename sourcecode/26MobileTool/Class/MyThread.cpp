#include "mythread.h"
#include <QDebug>




MyThread::MyThread(QObject *parent) :
	QThread(parent)
{
}

// run() will be called when a thread starts
void MyThread::run()
{
	for (int i = 0; i <= 100; i++)
	{
		int process = 0;
		// prevent other threads from changing the "Stop" value
		qDebug ()<< i << "chao ca nha";
		if (iSStop == true)
		{
			break;
		}
		// emit the signal for the count label
		process = i * 100 / 99;
		emit process_changed(process);

		emit valueChanged(i);
		
		// slowdown the count change, msec
		this->msleep(500);
	}
}
void MyThread::stop()
{
	iSStop = true;
}

