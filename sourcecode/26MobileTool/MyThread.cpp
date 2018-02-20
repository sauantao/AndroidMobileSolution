#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent, bool b) :
	QThread(parent), Stop(b)
{
}

// run() will be called when a thread starts
void MyThread::run()
{
	for (int i = 0; i <= 100; i++)
	{
		int process = 0;
		QMutex mutex;
		// prevent other threads from changing the "Stop" value
		mutex.lock();
		if (this->Stop) break;
		mutex.unlock();

		// emit the signal for the count label
		process = i * 100 / 99;
		emit process_changed(process);

		emit valueChanged(i);
		

		// slowdown the count change, msec
		this->msleep(500);
	}
}