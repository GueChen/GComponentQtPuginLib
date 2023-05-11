#ifndef __CUSTOM_WIDGETS_H
#define __CUSTOM_WIDGETS_H

#include "ColorCanvas/color_canvas_plugin.h"
#include "ColorEdit/color_edit_plugin.h"
#include "DragEdit/drageditplugin.h"
#include "Selector/selector_plugin.h"
#include "ClickedEdit/clicked_edit_plugin.h"
#include "AcrInstrument/acrinstrument_plugin.h"
#include "SwitchControl/switch_control_plugin.h"
#include "Vector3Edit/vector3_edit_plugin.h"

#include <QtDesigner/QtDesigner>
#include <QtCore/qplugin.h>

class CustomWidgets : public QObject, public QDesignerCustomWidgetCollectionInterface {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.GComponentQDesignerCollectionInterface")
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
	CustomWidgets(QObject* parnet = nullptr);

	QList<QDesignerCustomWidgetInterface*> customWidgets() const override;
private:
	QList<QDesignerCustomWidgetInterface*> widgets_;
};


#endif // !__CUSTOM_WIDGETS_H
