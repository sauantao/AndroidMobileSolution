#include "MainController.h"
#include "MainWindow.h"



MainController::MainController(QObject *parent, MainWindow *window) :
	QObject(parent),main_window(window)

{

}


MainController::~MainController()
{
}
