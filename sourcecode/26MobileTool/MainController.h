#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QtCore/QThread>
#include <list>

class MainWindow;


class MainController : public QObject
{
	Q_OBJECT
public:
	explicit MainController(QObject *parent, MainWindow * window);
	~MainController();

private:
	MainWindow *main_window;

};
#endif // MAINCONTROLLER_H
