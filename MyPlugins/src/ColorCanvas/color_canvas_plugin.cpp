#include "ColorCanvas/color_canvas.h"
#include "ColorCanvas/color_canvas_plugin.h"

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
    return "ColorCanvas";
}

QString ColorCanvasPlugin::group() const
{
    return QString("My Plugins");
}

QIcon ColorCanvasPlugin::icon() const
{
    return QIcon(":/icon/color canvas");
}

QString ColorCanvasPlugin::toolTip() const
{
    return QString("an editor to adjust and display color");
}

QString ColorCanvasPlugin::whatsThis() const
{
    return QString("a color diplay modeule could select and choose color");
}

bool ColorCanvasPlugin::isContainer() const
{
    return false;
}

QString ColorCanvasPlugin::domXml() const
{
    return "<widget class=\"ColorCanvas\" name=\"color_canvas\">\n"
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
    return "custom/color_canvas.h";
}