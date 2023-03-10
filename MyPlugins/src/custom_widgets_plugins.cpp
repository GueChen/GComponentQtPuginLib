#include "custom_widgets_plugins.h"

CustomWidgets::CustomWidgets(QObject* parent):
	QObject(parent)
{
	widgets_.append(new ColorCanvasPlugin(this));
	widgets_.append(new DragEditPlugin   (this));
	widgets_.append(new ColorEditPlugin  (this));
}

QList<QDesignerCustomWidgetInterface*> CustomWidgets::customWidgets() const {
	return widgets_;
}