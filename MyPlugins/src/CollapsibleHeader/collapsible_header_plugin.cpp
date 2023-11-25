#include "CollapsibleHeader/collapsible_header.h"
#include "CollapsibleHeader/collapsible_header_plugin.h"

CollapsibleHeaderPlugin::CollapsibleHeaderPlugin(QObject* parent)
	: QObject(parent)
{
	initialized = false;
}

void CollapsibleHeaderPlugin::initialize(QDesignerFormEditorInterface* core)
{
	if (initialized) return;

	initialized = true;
}

bool CollapsibleHeaderPlugin::isContainer() const
{
	return false;
}

bool CollapsibleHeaderPlugin::isInitialized() const
{
	return initialized;
}

QIcon CollapsibleHeaderPlugin::icon() const
{
	return QIcon();
}

QString CollapsibleHeaderPlugin::domXml() const
{
	return "<widget class=\"CollapsibleHeader\" name=\"collapsible_header\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>25</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString CollapsibleHeaderPlugin::group() const
{
	return "My Plugins";
}

QString CollapsibleHeaderPlugin::includeFile() const
{
	return "custom/collapsible_header.h";
}

QString CollapsibleHeaderPlugin::name() const
{
	return "CollapsibleHeader";
}

QString CollapsibleHeaderPlugin::toolTip() const
{
	return QString();
}

QString CollapsibleHeaderPlugin::whatsThis() const
{
	return QString();
}

QWidget* CollapsibleHeaderPlugin::createWidget(QWidget* parent)
{
	return new CollapsibleHeader(parent);
}

