#include "DragEdit/drag_edit.h"
#include "DragEdit/drageditplugin.h"

#include <QtCore/QtPlugin>

DragEditPlugin::DragEditPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void DragEditPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool DragEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget *DragEditPlugin::createWidget(QWidget *parent)
{
    return new DragEdit(parent);
}

QString DragEditPlugin::name() const
{
    return "Drag Edit";
}

QString DragEditPlugin::group() const
{
    return "My Plugins";
}

QIcon DragEditPlugin::icon() const
{
    return QIcon(":/icon/cat");
}

QString DragEditPlugin::toolTip() const
{
    return "an editor conatin value allowing drag to adjust (tool tips)";
}

QString DragEditPlugin::whatsThis() const
{
    return "An editor contain value allowing drag to adjust (whats this)";
}

bool DragEditPlugin::isContainer() const
{
    return false;
}

QString DragEditPlugin::domXml() const
{
    return "<widget class=\"DragEdit\" name=\"drag_edit\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>50</width>\n"
        "   <height>20</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString DragEditPlugin::includeFile() const
{
    return "custom/drag_edit.h";
}
