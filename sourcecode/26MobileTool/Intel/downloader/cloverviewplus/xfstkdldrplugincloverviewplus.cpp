
#include "xfstkdldrplugincloverviewplus.h"

//XfstkDldrPluginCloverviewPlus::XfstkDldrPluginCloverviewPlus()
//{
//    this->PluginInfo.PlatformName = QString("CloverviewPlus");
//    this->PluginInfo.PluginName = QString("CLV+ A0");
//    this->PluginInfo.PluginTabOrder = 3;
//
//    this->PluginInfo.PluginInterface = (XfstkDldrPluginInterface *)this;
//    QObject::connect(&(this->UserTabInterface),SIGNAL(UserInterfaceChanged(UserInterfaceState*)),&(this->OptionsTabInterface),SLOT(UserInterfaceChanged(UserInterfaceState*)));
//    QObject::connect(&(this->OptionsTabInterface),SIGNAL(OptionsInterfaceChanged(OptionsInterfaceState*)),&(this->UserTabInterface),SLOT(OptionsInterfaceChanged(OptionsInterfaceState*)));
//}

XfstkDldrPluginInterface* XfstkDldrPluginCloverviewPlus::Create()
{
    return new XfstkDldrPluginCloverviewPlus();
}

QTabWidget *XfstkDldrPluginCloverviewPlus::GetUserTabInterface()
{
    return this->UserTabInterface.GetTabInterface();
}

QTabWidget *XfstkDldrPluginCloverviewPlus::GetOptionsTabInterface()
{
    return this->OptionsTabInterface.GetTabInterface();
}

bool XfstkDldrPluginCloverviewPlus::InitializeTabInterfaces()
{
    return true;
}

bool XfstkDldrPluginCloverviewPlus::SaveTabInterfaceSettings()
{
    this->UserTabInterface.SaveUserInterfaceStateToDisk(QString("Intel"),QString("CloverviewPlus"));
    return true;
}

bool XfstkDldrPluginCloverviewPlus::RestoreTabInterfaceSettings()
{
    this->UserTabInterface.LoadUserInterfaceStateFromDisk(QString("Intel"),QString("CloverviewPlus"));
    this->UserTabInterface.RestoreUserInterfaceFromCurrentState();
    return true;
}

XfstkDldrPluginInfo *XfstkDldrPluginCloverviewPlus::GetPluginInfo()
{
    return &(this->PluginInfo);
}

bool XfstkDldrPluginCloverviewPlus::Init()
{
    return true;
}

//Q_EXPORT_PLUGIN2(XfstkDldrPluginCloverviewPlus, XfstkDldrPluginCloverviewPlus)
