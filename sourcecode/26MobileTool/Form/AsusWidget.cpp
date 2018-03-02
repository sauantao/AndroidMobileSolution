#include "AsusWidget.h"
#include "ui_AsusWidget.h"
#include <sstream> 
#include <iostream>  
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <conio.h>
#include <list>
#include <QFileDialog>



using namespace std;

//typedef basic_istringstream<_TCHAR> ITSS;
//
//#define USE_JUNGO_USB
//
//HANDLE ghMutex;
//HANDLE ghListMutex;
//
//list<string> list_usbsn;
//list<string>::iterator it_usbsn;
//list<void*> list_running;
//list<void*> list_done;
//list<void*>::iterator it_running;
//list<void*>::iterator it_done;
//int totaltargets = 1;
//int donetargets = 0;
//int failtargets = 0;
//
////For using dynamic xfstk API load
//typedef xfstkdldrapi* (*PXFSTKALLOC) ();
//typedef  void(*PXFSTKDEALLOC) (xfstkdldrapi*);
//
//HINSTANCE hinstLib;
//PXFSTKALLOC xfstkalloc;
//PXFSTKDEALLOC xfstkdealloc;
//class ThreadObj
//{
//public:
//	ThreadObj();
//	HANDLE Start(void * arg);
//	unsigned int GetID() { return ThreadId_; }
//protected:
//	unsigned Run(void * arg);
//	static unsigned __stdcall EntryPoint(void*);
//	virtual void Setup();
//	virtual void Execute(void*);
//	void * Arg() const { return Arg_; }
//	void Arg(void* a) { Arg_ = a; }
//private:
//	unsigned int ThreadId_;
//	void * Arg_;
//
//};
//
//
//
//typedef struct {
//
//	string fwdnx;
//	string fwimage;
//	string osdnx;
//	string osimage;
//	string gpflags;
//	string usbsn;
//	string softfuse;
//	xfstkstatuspfn statuscallback;
//} arg_type;
//
//typedef struct {
//
//	void* threadobj;
//	string usbsn;
//	HANDLE hthread;
//} thread_rectype;
//
//ThreadObj::ThreadObj() {}
//
//HANDLE ThreadObj::Start(void * arg)
//{
//	Arg(arg); // store user data
//			  //int code = thread_create(ThreadObj::EntryPoint, this, & ThreadId_);
//	return (HANDLE)_beginthreadex(NULL,        /* Security attributes (NULL = default) */
//		0U,          /* Stack size (0 = default) */
//		ThreadObj::EntryPoint,  /* Address of thread callback */
//		(void *)this, /* Argument casted to void pointer */
//		0U,          /* Creation flag (0 = not suspended) */
//		&ThreadId_);/* Pointer to thread ID value */
//}
//
//unsigned ThreadObj::Run(void * arg)
//{
//	Setup();
//	Execute(arg);
//	return 1;
//}
//
///*static */
//unsigned ThreadObj::EntryPoint(void * pthis)
//{
//	ThreadObj * pt = (ThreadObj*)pthis;
//	return pt->Run(pt->Arg());
//}
//
//void ThreadObj::Setup()
//{
//}
//
//void ThreadObj::Execute(void* arg)
//{
//	bool bResult = false;
//	LastError er;
//	thread_rectype * trd;
//	arg_type * myarg = (arg_type*)arg;
//	if (NULL == hinstLib)
//		return;
//	if (NULL == xfstkalloc)
//		return;
//	if (NULL == xfstkdealloc)
//		return;
//	xfstkdldrapi* xfstktest = xfstkalloc();
//	if (NULL == xfstktest)
//		return;
//
//	xfstkstatuspfn mystatusfn = myarg->statuscallback;
//
//	xfstktest->registerstatuscallback(mystatusfn, this);
//	xfstktest->settargetretrycount(20);
//	xfstktest->setwipeifwi(false);
//
//	bResult = xfstktest->downloadmtfwosasync(
//		(char*)myarg->fwdnx.c_str(),
//		(char*)myarg->fwimage.c_str(),
//		(char*)myarg->osdnx.c_str(),
//		(char*)myarg->osimage.c_str(),
//		(char*)myarg->gpflags.c_str(),
//		(char*)myarg->usbsn.c_str(),
//		(char*)myarg->softfuse.c_str()
//	);
//	xfstktest->getlasterror(&er);
//
//	printf("USBSN: %s -- Downloader thread %d Returned error code:%d -- %s\n", myarg->usbsn.c_str(), ThreadId_, er.error_code, er.error_message);
//
//	WaitForSingleObject(ghListMutex, INFINITE);
//	for (list<void*>::iterator it = list_running.begin(); it != list_running.end(); it++) {
//		trd = (thread_rectype *)*it;
//		if (trd->usbsn == myarg->usbsn) {
//
//			//list_running.remove(*it);
//			list_done.push_back(*it);
//			donetargets++;
//			if (er.error_code != 0)
//				failtargets++;
//			break;
//		}
//	}
//	ReleaseMutex(ghListMutex);
//	xfstkdealloc(xfstktest);
//}
//
//bool IsContains(list<void*>* list_checking, string* usbsn)
//{
//	bool ret = false;
//	WaitForSingleObject(ghListMutex, INFINITE);
//	for (list<void*>::iterator it = list_checking->begin(); it != list_checking->end(); it++) {
//		thread_rectype *trd = (thread_rectype *)*it;
//		if (trd->usbsn == *usbsn) {
//			ret = true;
//			break;
//		}
//	}
//	ReleaseMutex(ghListMutex);
//	return ret;
//}
//
//#ifdef USE_JUNGO_USB
//int DetectDevices()
//{
//	int num_devices = 0;
//	if (NULL == hinstLib)
//		return 0;
//	if (NULL == xfstkalloc)
//		return 0;
//	if (NULL == xfstkdealloc)
//		return 0;
//
//	xfstkdldrapi* xfstktest = xfstkalloc();
//
//	if (NULL == xfstktest)
//		return 0;
//
//	SoCDevices soc_devices;
//	list_usbsn.clear();
//	num_devices = xfstktest->getavailabletargets(&soc_devices);
//	for (int i = 0; i < soc_devices.number_devices; i++) {
//		list_usbsn.push_back(soc_devices.soc_device[i].usbsn);
//	}
//	xfstkdealloc(xfstktest);
//	return num_devices;
//}
//#endif 
//
//void  AsusWidget::status(char *message, void *clientdata)
//{
//
//	WaitForSingleObject(
//		ghMutex,    // handle to mutex
//		INFINITE);  // 200 ms timeout
//	QString msg;
//	log(kLogTypeInfo, msg.sprintf("ThreadID-- %d-- %s", ((ThreadObj *)clientdata)->GetID(), message));
//	//printf("ThreadID -- %d -- %s", ((ThreadObj *)clientdata)->GetID(), message);
//	//printf(message);
//	ReleaseMutex(ghMutex);
//}
//void status(char *message, void *clientdata)
//{
//
//	WaitForSingleObject(
//		ghMutex,    // handle to mutex
//		INFINITE);  // 200 ms timeout
//	//QString msg;
//	//log(kLogTypeInfo, msg.sprintf("ThreadID-- %d-- %s", ((ThreadObj *)clientdata)->GetID(), message));
//	//printf("ThreadID -- %d -- %s", ((ThreadObj *)clientdata)->GetID(), message);
//	//printf(message);
//	ReleaseMutex(ghMutex);
//}
//
//int Unbrick()
//{
//	int y = 0;
//	int pass = 0;
//	int fail = 0;
//	char xfstk_version[32];
//
//	hinstLib = LoadLibrary(TEXT(".\\xfstk-dldr-api.dll")); // NOTE: The use of double back-slashes.
//	if (NULL == hinstLib)
//		return -1;
//	xfstkalloc = (PXFSTKALLOC)GetProcAddress(hinstLib, (LPCSTR)"xfstkdldrapi_alloc");
//	if (NULL == xfstkalloc)
//		return -1;
//	xfstkdealloc = (PXFSTKDEALLOC)GetProcAddress(hinstLib, (LPCSTR)"xfstkdldrapi_dealloc");
//	if (NULL == xfstkdealloc)
//		return -1;
//
//	xfstkdldrapi* xfstktest = xfstkalloc();
//
//	if (NULL == xfstktest)
//		return -1;
//
//	int retrycount = 20;
//
//	bool provisioningok = false;
//
//	xfstktest->getversion(xfstk_version);
//	QString msg;
//	//log(kLogTypeInfo, msg.sprintf("XFSTK Downloader API version : %s\n", xfstk_version));
//	//printf("XFSTK Downloader API version: %s\n", xfstk_version);
//
//	//Note: Parallel Asynchronous multi-target download is only supported for 
//	//MFLD D1 or D0 with USB serial number ROM patched IFWI  
//	//test.setmtdownloadtype(MT_PARALLEL_SYNC);
//
//	ghMutex = CreateMutex(
//		NULL,              // default security attributes
//		FALSE,             // initially not owned
//		NULL);             // unnamed mutex
//
//	if (ghMutex == NULL)
//	{
//		QString msg;
//		//log(kLogTypeInfo, msg.sprintf("CreateMutex error: %d\n", GetLastError()));
//		//printf("CreateMutex error: %d\n", GetLastError());
//		return 1;
//	}
//
//	ghListMutex = CreateMutex(
//		NULL,              // default security attributes
//		FALSE,             // initially not owned
//		NULL);             // unnamed mutex
//
//	if (ghListMutex == NULL)
//	{
//		//printf("CreateMutex error: %d\n", GetLastError());
//		QString msg;
//		//log(kLogTypeInfo, msg.sprintf("CreateMutex error: %0\n", GetLastError()));
//		return 1;
//	}
//
//	//printf("\n\nXFSTK INFO: Total targets requested for programming: %d\n", totaltargets);
//
//	//QString msg;
//	//log(kLogTypeInfo, msg.sprintf("\n\nXFSTK INFO: Total targets requested for programming: %0\n", totaltargets));
//
//	it_running = list_running.begin();
//	it_done = list_done.begin();
//	it_usbsn = list_usbsn.begin();
//
//	//Here populate list_usbsn for simulate the SCU device dection
//	//Remeber replace the ussn string with the ones from your devices
//#ifndef USE_JUNGO_USB
//
//	list_usbsn.push_back("175D126E48335F80");
//	list_usbsn.push_back("BDA397C26EA8035B");
//	list_usbsn.push_back("3183CBBBDA014AF1");
//	//list_usbsn.insert (it_usbsn++,"C3D09A327432D29A");
//	list_usbsn.push_back("B9AD3AC29A0BDF5E");
//	list_usbsn.push_back("4EC224787F0ECABB");
//	list_usbsn.push_back("9724D645A3D7E902");
//	list_usbsn.push_back("E7C123BC1EA72083");
//
//	//Wait to see if there is a new device arrived
//	while (1) {
//		if (xfstktest->getavailabletargets() > 0) {
//			printf("\n\nXFSTK INFO: Found SCU %d devices.\n", xfstktest->getavailabletargets());
//			break;
//		}
//
//		//Sleep one second and scan a again
//		printf("\n\nXFSTK INFO: Wait One seconds and scan for SCU device again\n");
//		Sleep(1000);//(1000);
//	}
//#else 
//	//Use Jungo driver port mapping to detect USBSN 
//	while (1) {
//		if (DetectDevices() == totaltargets)
//			break;
//		//printf("\n\nXFSTK INFO: Wait 500ms and scan for SCU device again\n");
//		QString msg;
//		//log(kLogTypeInfo, msg.sprintf("\n\nXFSTK INFO : Wait 500ms and scan for SCU device again\n"));
//		Sleep(1000);
//	}
//#endif 
//
//	while (1) {
//		//In your App, need to use winddk USB enumeration to detect SCU devices
//		//here only use populated list_usbsn to simulate
//		for (it_usbsn = list_usbsn.begin(); it_usbsn != list_usbsn.end(); it_usbsn++) {
//			//cout << "USBSN: \n" << *it_usbsn;
//			if (!IsContains(&list_running, &*it_usbsn)) {
//				thread_rectype * thread_rec = new thread_rectype;
//				ThreadObj* downloader = new ThreadObj;
//				thread_rec->threadobj = (void*)downloader;
//				thread_rec->usbsn = *it_usbsn;
//
//				WaitForSingleObject(ghListMutex, INFINITE);
//				list_running.push_back((void*)thread_rec);
//				ReleaseMutex(ghListMutex);
//
//				arg_type * myarg = new arg_type;
//				myarg->fwdnx = "C:\\Asus\\sec-dnx_fwr.bin";
//				myarg->fwimage = "C:\\Asus\\sec-ifwi-prod.bin";
//				myarg->osdnx = "C:\\Asus\\sec-dnx_osr.bin";
//				myarg->osimage = "C:\\Asus\\droidboot.img.POS_sign.bin";
//				myarg->gpflags = "80000041";
//				myarg->usbsn = *it_usbsn;
//
//				
//				myarg->statuscallback = status;
//
//				//log(kLogTypeInfo,"Starting thread on USBSN: " + *it_usbsn + "\n");
//
//				//cout << "Starting thread on USBSN: " + *it_usbsn << "\n";
//
//				thread_rec->hthread = downloader->Start((void*)myarg);
//				//Wait 200ms to let the thread to start
//				Sleep(200);
//			}
//		}
//
//		//If done clear up all resources 
//		if (donetargets >= totaltargets) {
//			WaitForSingleObject(ghListMutex, INFINITE);
//
//			while (!list_done.empty()) {
//				thread_rectype *trd = (thread_rectype *)list_done.front();
//				list_done.pop_front();
//				CloseHandle(trd->hthread);
//				delete trd->threadobj;
//				delete trd;
//			}
//			list_done.clear();
//			list_running.clear();
//
//			if (failtargets > 0) {
//				fail += failtargets;
//				pass += donetargets;
//				pass -= failtargets;
//
//				QString msg;
//				//log(kLogTypeInfo, msg.sprintf("\n\nXFSTK ERROR: %d devices failed out of %d\n", fail, donetargets));
//				//printf("\n\nXFSTK ERROR: %d devices failed out of %d\n", fail, donetargets);
//			}
//			else {
//				pass += donetargets;
//				//printf("\n\nXFSTK INFO: %d devices soccessful out of %d\n", pass, donetargets);
//				QString msg;
//				//log(kLogTypeInfo, msg.sprintf("\n\nXFSTK INFO: %d devices soccessful out of %d\n", pass, donetargets));
//			}
//			//clear the variables for next round of run 
//			donetargets = failtargets = 0;
//			ReleaseMutex(ghListMutex);
//			break;
//		}
//
//		//wait one second to check if threads are done
//		Sleep(1000);
//
//	}
//
//	//cout << "Press any key to terminate this program. "; //getch();
//
//	CloseHandle(ghMutex);
//	CloseHandle(ghListMutex);
//	xfstkdealloc(xfstktest);
//	FreeLibrary(hinstLib);
//	exit(0);
//}
//
///////////////////////////////////////////////////

AsusWidget::AsusWidget(QTabWidget *parent, MainWindow *window) :
	TabWidgetBase(5, tr("&Asus Widget"), parent),ui(new Ui::AsusWidget),main_window(window)
{
	ui->setupUi(this);

}
AsusWidget::~AsusWidget()
{
	delete ui;
}
void AsusWidget::LockOnUI()
{
	//enableControl(false);
}

void AsusWidget::DoFinished()
{
	//enableControl(true);
}

void AsusWidget::UpdateUI()
{
	ui->retranslateUi(this);
}

void AsusWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
	QString label = "CMD";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

	tab_widget->setTabText(index, label);
}

void AsusWidget::SetShortCut(int, const QString &)
{

}



//int AsusWidget::UnBrick()
//{
//	
//	exit(0);
//}
void AsusWidget::log(int type, const char* message) {
	QString tmp = "gray";

	switch (type) {
	case kLogTypeDebug:		tmp = "gray";	break;
	case kLogTypeError:		tmp = "red";	break;
	case kLogTypeWarning:	tmp = "orange";	break;
	case kLogTypeInfo:		tmp = "green";	break;
	}

	ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message));
}

void AsusWidget::log(int type, std::string message)
{
	QString tmp = "gray";

	switch (type) {
	case kLogTypeDebug:		tmp = "gray";	break;
	case kLogTypeError:		tmp = "red";	break;
	case kLogTypeWarning:	tmp = "orange";	break;
	case kLogTypeInfo:		tmp = "green";	break;
	}

	ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message.c_str()));
}

void AsusWidget::log(int type, QString message)
{

	QString tmp = "gray";

	switch (type) {
	case kLogTypeDebug:		tmp = "gray";	break;
	case kLogTypeError:		tmp = "red";	break;
	case kLogTypeWarning:	tmp = "orange";	break;
	case kLogTypeInfo:		tmp = "green";	break;
	}

	ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message.toStdString().c_str()));
}
void AsusWidget::on_pushButton_Start_clicked()
{
	//Unbrick();
}

void AsusWidget::on_pushButton_fwdnx_clicked()
{
	QString fwdnx = QFileDialog::getOpenFileName(this, QString::fromUtf8(" Chọn file FWDNX "), "d:\\", "fwdnx*.*");
	ui->lineEdit_fwdnx->setText(fwdnx);

}

void AsusWidget::on_pushButton_fwimage_clicked()
{
	QString fwimage = QFileDialog::getOpenFileName(this, QString::fromUtf8(" Chọn file FWIMAGE"), "d:\\", "fwimage*.*");
	ui->lineEdit_fwimage->setText(fwimage);
}

void AsusWidget::on_pushButton_osdnx_clicked()
{
	QString osdnx = QFileDialog::getOpenFileName(this, QString::fromUtf8(" Chọn file OSDNX"), "d:\\", "oxdnx*.*");
	ui->lineEdit_osdnx->setText(osdnx);
}

void AsusWidget::on_pushButton_osimage_clicked()
{
	QString osimage = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file OS IMAGE"), "d:\\", "osimage*.*");
	ui->lineEdit_osimage->setText(osimage);
}
