#include "ClickedEdit/clicked_edit.h"
#include "ClickedEdit/clicked_edit_plugin.h"

#include <QtCore/QtPlugin>

ClickedEditPlugin::ClickedEditPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void ClickedEditPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool ClickedEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget* ClickedEditPlugin::createWidget(QWidget* parent)
{
    return new ClickedEdit(parent);
}

QString ClickedEditPlugin::name() const
{
    return "Clicked Edit";
}

QString ClickedEditPlugin::group() const
{
    return "My Plugins";
}

QIcon ClickedEditPlugin::icon() const
{
    return QIcon("");
}

QString ClickedEditPlugin::toolTip() const
{
    return "an edit supply an clicked signals";
}

QString ClickedEditPlugin::whatsThis() const
{
    return "";
}

bool ClickedEditPlugin::isContainer() const
{
    return false;
}

QString ClickedEditPlugin::domXml() const
{
    return "<widget class=\"ClickedEdit\" name=\"clicked_edit\">\n"        
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>50</width>\n"
        "   <height>25</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString ClickedEditPlugin::includeFile() const
{
    return "custom/clicked_edit.h";
}