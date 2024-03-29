#include "ClickedEdit/clicked_edit.h"

#include <QtGui/QMouseEvent>

ClickedEdit::ClickedEdit(QWidget* parent):
	ClickedEdit("", parent)
{}

ClickedEdit::ClickedEdit(const QString& text, QWidget* parent):
	QLineEdit(text, parent)
{
	setStyleSheet("QLineEdit{"
		"font:  9pt \"Cascadia Code\";"
		"color: black;"
		"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
		"                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
		"border: 1px solid gray;"
		"border-radius: 3px;"
		"}"
		"QLineEdit::hover{"
		"font:  9pt \"Cascadia Code\";"
		"color: #FFFFEE;"
		"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"                                 stop: 0 #AAAAAA, stop: 0.4 #BBBBBB,"
		"                                 stop: 0.5 #A8A8A8, stop: 1.0 #B3B3B3);"
		"border: 2px solid #dfdfdf;"
		"border-radius: 3px;"
		"}"
	);
}

void ClickedEdit::mouseReleaseEvent(QMouseEvent* event)
{	
	if (event->button() == Qt::LeftButton && geometry().contains(mapToParent(event->pos()))) {
		emit Clicked();
	}
}
