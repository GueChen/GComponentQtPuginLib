#include "custom_widgets_plugins.h"

CustomWidgets::CustomWidgets(QObject* parent):
	QObject(parent)
{
	widgets_.append(new ColorCanvasPlugin      (this));
	widgets_.append(new DragEditPlugin         (this));
	widgets_.append(new ColorEditPlugin        (this));
	widgets_.append(new GSelectorPlugin        (this));
	widgets_.append(new ClickedEditPlugin      (this));
	widgets_.append(new AcrInstrumentPlugin    (this));
	widgets_.append(new SwitchControlPlugin    (this));
	widgets_.append(new Vector3EditPlugin      (this));
	widgets_.append(new CollapsibleHeaderPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> CustomWidgets::customWidgets() const {
	return widgets_;
}