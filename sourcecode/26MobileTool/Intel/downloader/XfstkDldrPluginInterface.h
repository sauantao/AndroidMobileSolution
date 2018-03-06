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
#ifndef XFSTKDLDRPLUGININTERFACE_H
#define XFSTKDLDRPLUGININTERFACE_H
#include <QStringList>
#include <QTabWidget>

class XfstkDldrPluginInterface;

struct XfstkDldrPluginInfo {
    QString PluginName;
    QString PlatformName;
    int PluginTabOrder;
    XfstkDldrPluginInterface *PluginInterface;
};

class XfstkDldrPluginInterface
{
public:
    virtual XfstkDldrPluginInterface* Create() = 0;
    virtual QTabWidget *GetUserTabInterface() = 0;
    virtual QTabWidget *GetOptionsTabInterface() = 0;
    virtual bool InitializeTabInterfaces() = 0;
    virtual bool SaveTabInterfaceSettings() = 0;
    virtual bool RestoreTabInterfaceSettings() = 0;
    virtual XfstkDldrPluginInfo *GetPluginInfo() = 0;
    virtual bool Init() = 0;
    virtual ~XfstkDldrPluginInterface() {}
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(XfstkDldrPluginInterface,
                    "com.Intel.SCU.XFSTK.Dldr.Plugin/1.0");
QT_END_NAMESPACE

#endif // XFSTKDLDRPLUGININTERFACE_H
