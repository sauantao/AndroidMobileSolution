#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = 0, bool b = false);
	void run();

	// if Stop = true, the thread will break
	// out of the loop, and will be disposed
	bool Stop;

signals:
	// To communicate with Gui Thread
	// we need to emit a signal
	void valueChanged(int);
	void process_changed(int);

	public slots:

};

#endif // MYTHREAD_H
