#include "Selector/selector.h"
#include "Selector/selector_plugin.h"

#include <QtCore/QtPlugin>

GSelectorPlugin::GSelectorPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void GSelectorPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool GSelectorPlugin::isInitialized() const
{
    return initialized;
}

QWidget* GSelectorPlugin::createWidget(QWidget* parent)
{
    return new GSelector(parent);
}

QString GSelectorPlugin::name() const
{
    return "GSelector";
}

QString GSelectorPlugin::group() const
{
    return "My Plugins";
}

QIcon GSelectorPlugin::icon() const
{
    return QIcon(":/icon/shader_icon");
}

QString GSelectorPlugin::toolTip() const
{
    return "an display edit supply an inteface to choose contex from list";
}

QString GSelectorPlugin::whatsThis() const
{
    return "";
}

bool GSelectorPlugin::isContainer() const
{
    return false;
}

QString GSelectorPlugin::domXml() const
{
    return "<widget class=\"GSelector\" name=\"selector\">\n"        
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

QString GSelectorPlugin::includeFile() const
{
    return "custom/selector.h";
}