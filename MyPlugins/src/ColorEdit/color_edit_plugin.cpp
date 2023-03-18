#include "ColorEdit/color_edit.h"
#include "ColorEdit/color_edit_plugin.h"

#include <QtCore/QtPlugin>

ColorEditPlugin::ColorEditPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void ColorEditPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool ColorEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget* ColorEditPlugin::createWidget(QWidget* parent)
{
    return new ColorEdit(parent);
}

QString ColorEditPlugin::name() const
{
    return "ColorEdit";
}

QString ColorEditPlugin::group() const
{
    return "My Plugins";
}

QIcon ColorEditPlugin::icon() const
{
    return QIcon(":/icon/color");
}

QString ColorEditPlugin::toolTip() const
{
    return "an editor to adjust and display color";
}

QString ColorEditPlugin::whatsThis() const
{
    return "";
}

bool ColorEditPlugin::isContainer() const
{
    return false;
}

QString ColorEditPlugin::domXml() const
{
    return "<widget class=\"ColorEdit\" name=\"color_edit\">\n"        
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>300</width>\n"
        "   <height>65</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString ColorEditPlugin::includeFile() const
{
    return "custom/color_edit.h";
}