#include "color_canvas.h"
#include "color_canvas_plugin.h"

#include <QtCore/QtPlugin>

ColorCanvasPlugin::ColorCanvasPlugin(QObject* parent)
    : QObject(parent)
{
    initialized = false;
}

void ColorCanvasPlugin::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool ColorCanvasPlugin::isInitialized() const
{
    return initialized;
}

QWidget* ColorCanvasPlugin::createWidget(QWidget* parent)
{
    return new ColorCanvas(parent);
}

QString ColorCanvasPlugin::name() const
{
    return "Color Canvas";
}

QString ColorCanvasPlugin::group() const
{
    return "My Plugins";
}

QIcon ColorCanvasPlugin::icon() const
{
    return QIcon(":/icon/color");
}

QString ColorCanvasPlugin::toolTip() const
{
    return "an editor to adjust and display color";
}

QString ColorCanvasPlugin::whatsThis() const
{
    return "";
}

bool ColorCanvasPlugin::isContainer() const
{
    return false;
}

QString ColorCanvasPlugin::domXml() const
{
    return "<widget class=\"ColorCanvas\" name=\"ColorCanvas\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>50</width>\n"
        "   <height>50</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString ColorCanvasPlugin::includeFile() const
{
    return "custom\\color_canvas.h";
}