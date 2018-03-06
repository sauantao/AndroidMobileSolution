/*
    Copyright (C) 2015  Intel Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "xfstkdldrpluginbaytrail.h"

XfstkDldrPluginBaytrail::XfstkDldrPluginBaytrail()
{
    this->PluginInfo.PlatformName = QString("Baytrail");
    this->PluginInfo.PluginName = QString("Baytrail B0");
    this->PluginInfo.PluginTabOrder = 1;

    this->PluginInfo.PluginInterface = (XfstkDldrPluginInterface *)this;
    QObject::connect(&(this->UserTabInterface),SIGNAL(UserInterfaceChanged(UserInterfaceState*)),&(this->OptionsTabInterface),SLOT(UserInterfaceChanged(UserInterfaceState*)));
    QObject::connect(&(this->OptionsTabInterface),SIGNAL(OptionsInterfaceChanged(OptionsInterfaceState*)),&(this->UserTabInterface),SLOT(OptionsInterfaceChanged(OptionsInterfaceState*)));
}

XfstkDldrPluginInterface* XfstkDldrPluginBaytrail::Create()
{
    return new XfstkDldrPluginBaytrail();
}

QTabWidget *XfstkDldrPluginBaytrail::GetUserTabInterface()
{
    return this->UserTabInterface.GetTabInterface();
}

QTabWidget *XfstkDldrPluginBaytrail::GetOptionsTabInterface()
{
    return this->OptionsTabInterface.GetTabInterface();
}

bool XfstkDldrPluginBaytrail::InitializeTabInterfaces()
{
    return true;
}

bool XfstkDldrPluginBaytrail::SaveTabInterfaceSettings()
{
    this->UserTabInterface.SaveUserInterfaceStateToDisk(QString("Intel"),QString("Baytrail"));
    return true;
}

bool XfstkDldrPluginBaytrail::RestoreTabInterfaceSettings()
{
    this->UserTabInterface.LoadUserInterfaceStateFromDisk(QString("Intel"),QString("Baytrail"));
    this->UserTabInterface.RestoreUserInterfaceFromCurrentState();
    return true;
}

XfstkDldrPluginInfo *XfstkDldrPluginBaytrail::GetPluginInfo()
{
    return &(this->PluginInfo);
}

bool XfstkDldrPluginBaytrail::Init()
{
    return true;
}

Q_EXPORT_PLUGIN2(XfstkDldrPluginBaytrail, XfstkDldrPluginBaytrail)
