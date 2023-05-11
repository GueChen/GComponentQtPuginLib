#include "Vector3Edit/vector3_edit.h"
#include "Vector3Edit/vector3_edit_plugin.h"

#include <QtCore/QtPlugin>

Vector3EditPlugin::Vector3EditPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void Vector3EditPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool Vector3EditPlugin::isInitialized() const
{
    return initialized;
}

QWidget* Vector3EditPlugin::createWidget(QWidget* parent)
{
    return new Vector3Edit(parent);
}

QString Vector3EditPlugin::name() const
{
    return "Vector3Edit";
}

QString Vector3EditPlugin::group() const
{
    return "My Plugins";
}

QIcon Vector3EditPlugin::icon() const
{
    return QIcon(":/icon/vec edit");
}

QString Vector3EditPlugin::toolTip() const
{
    return "an editor to adjust vector3 value";
}

QString Vector3EditPlugin::whatsThis() const
{
    return "";
}

bool Vector3EditPlugin::isContainer() const
{
    return false;
}

QString Vector3EditPlugin::domXml() const
{
    return "<widget class=\"Vector3Edit\" name=\"vector3_edit\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>250</width>\n"
        "   <height>45</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString Vector3EditPlugin::includeFile() const
{
    return "custom/vector3_edit.h";
}