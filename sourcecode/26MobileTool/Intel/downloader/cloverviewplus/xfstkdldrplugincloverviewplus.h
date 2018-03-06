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
#ifndef XFSTKDLDRPLUGINCLOVERVIEWPLUS_H
#define XFSTKDLDRPLUGINCLOVERVIEWPLUS_H
#include "../XfstkDldrPluginTemplate_global.h"
#include "../XfstkDldrPluginInterface.h"

#include "xfstkdldrpluginuserinterface.h"
#include "xfstkdldrpluginoptionsinterface.h"

#include <QtCore/qplugin.h>

class XFSTKDLDRPLUGINTEMPLATESHARED_EXPORT XfstkDldrPluginCloverviewPlus : public QObject, public XfstkDldrPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(XfstkDldrPluginInterface)

public:
    XfstkDldrPluginCloverviewPlus();
    XfstkDldrPluginInfo PluginInfo;
    bool Init();
    XfstkDldrPluginInterface* Create();
    QTabWidget *GetUserTabInterface();
    QTabWidget *GetOptionsTabInterface();
    bool InitializeTabInterfaces();
    bool SaveTabInterfaceSettings();
    bool RestoreTabInterfaceSettings();
    XfstkDldrPluginInfo *GetPluginInfo();
    XfstkDldrPluginUserInterface UserTabInterface;
    XfstkDldrPluginOptionsInterface OptionsTabInterface;

};

#endif // XFSTKDLDRPLUGINCLOVERVIEWPLUS_H
