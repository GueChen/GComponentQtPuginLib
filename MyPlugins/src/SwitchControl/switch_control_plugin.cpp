#include "SwitchControl/switch_control.h"
#include "SwitchControl/switch_control_plugin.h"

#include <QtCore/QtPlugin>

SwitchControlPlugin::SwitchControlPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void SwitchControlPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool SwitchControlPlugin::isInitialized() const
{
    return initialized;
}

QWidget* SwitchControlPlugin::createWidget(QWidget* parent)
{
    return new SwitchControl(parent);
}

QString SwitchControlPlugin::name() const
{
    return "SwitchControl";
}

QString SwitchControlPlugin::group() const
{
    return "CC Plugins";
}

QIcon SwitchControlPlugin::icon() const
{
    return QIcon("");
}

QString SwitchControlPlugin::toolTip() const
{
    return "an switch like boolean controller";
}

QString SwitchControlPlugin::whatsThis() const
{
    return "";
}

bool SwitchControlPlugin::isContainer() const
{
    return false;
}

QString SwitchControlPlugin::domXml() const
{
    return "<widget class=\"SwitchControl\" name=\"switch_control\">\n"        
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

QString SwitchControlPlugin::includeFile() const
{
    return "custom/switch_control.h";
}