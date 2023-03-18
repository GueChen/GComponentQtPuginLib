#include "AcrInstrument/acrinstrument.h"
#include "AcrInstrument/acrinstrument_plugin.h"

#include <QtCore/QtPlugin>

AcrInstrumentPlugin::AcrInstrumentPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void AcrInstrumentPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool AcrInstrumentPlugin::isInitialized() const
{
    return initialized;
}

QWidget* AcrInstrumentPlugin::createWidget(QWidget* parent)
{
    return new AcrInstrument(parent);
}

QString AcrInstrumentPlugin::name() const
{
    return "AcrInstrument";
}

QString AcrInstrumentPlugin::group() const
{
    return "CC Plugins";
}

QIcon AcrInstrumentPlugin::icon() const
{
    return QIcon("");
}

QString AcrInstrumentPlugin::toolTip() const
{
    return "an acrinstrument like vehicles";
}

QString AcrInstrumentPlugin::whatsThis() const
{
    return "";
}

bool AcrInstrumentPlugin::isContainer() const
{
    return false;
}

QString AcrInstrumentPlugin::domXml() const
{
    return "<widget class=\"AcrInstrument\" name=\"acr_instrument\">\n"        
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString AcrInstrumentPlugin::includeFile() const
{
    return "custom/acrinstrument.h";
}