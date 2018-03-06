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
#include "xfstkdldrpluginmedfield.h"

XfstkDldrPluginMedfield::XfstkDldrPluginMedfield()
{
    this->PluginInfo.PlatformName = QString("Medfield");
    this->PluginInfo.PluginName = QString("Medfield B0/C0");
    this->PluginInfo.PluginTabOrder = 0;
    this->PluginInfo.PluginInterface = (XfstkDldrPluginInterface *)this;
    QObject::connect(&(this->UserTabInterface),SIGNAL(UserInterfaceChanged(UserInterfaceState*)),&(this->OptionsTabInterface),SLOT(UserInterfaceChanged(UserInterfaceState*)));
    QObject::connect(&(this->OptionsTabInterface),SIGNAL(OptionsInterfaceChanged(OptionsInterfaceState*)),&(this->UserTabInterface),SLOT(OptionsInterfaceChanged(OptionsInterfaceState*)));
}

XfstkDldrPluginInterface* XfstkDldrPluginMedfield::Create()
{
    return new XfstkDldrPluginMedfield();
}

QTabWidget *XfstkDldrPluginMedfield::GetUserTabInterface()
{
    return this->UserTabInterface.GetTabInterface();
}

QTabWidget *XfstkDldrPluginMedfield::GetOptionsTabInterface()
{
    return this->OptionsTabInterface.GetTabInterface();
}

bool XfstkDldrPluginMedfield::InitializeTabInterfaces()
{
    return true;
}

bool XfstkDldrPluginMedfield::SaveTabInterfaceSettings()
{
    this->UserTabInterface.SaveUserInterfaceStateToDisk(QString("Intel"),QString("Medfield"));
    return true;
}

bool XfstkDldrPluginMedfield::RestoreTabInterfaceSettings()
{
    this->UserTabInterface.LoadUserInterfaceStateFromDisk(QString("Intel"),QString("Medfield"));
    this->UserTabInterface.RestoreUserInterfaceFromCurrentState();
    return true;
}

XfstkDldrPluginInfo *XfstkDldrPluginMedfield::GetPluginInfo()
{
    return &(this->PluginInfo);
}

bool XfstkDldrPluginMedfield::Init()
{
    return true;
}

Q_EXPORT_PLUGIN2(XfstkDldrPluginMedfield, XfstkDldrPluginMedfield)
