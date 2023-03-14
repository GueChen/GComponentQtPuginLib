#include "Selector/selector.h"

#include "ui_selector_dialog.h"

#include <QtGui/QMouseEvent>

GSelector::GSelector(QWidget* parent, const QString& value, const QStringList& values):
	QLineEdit(parent),
	dialog_ui_ptr_(new Ui::ListSelectorDialog)
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

	setText(value);
	setReadOnly(true);
	setAlignment(Qt::AlignHCenter);	
	
	list_dialog_.setWindowTitle("selection");
	list_dialog_.setWindowIcon(QIcon(":/icon/shader_icon"));

	dialog_ui_ptr_->setupUi(&list_dialog_);
	
	dialog_ui_ptr_->shader_list->setSelectionMode(QAbstractItemView::SingleSelection);	
	dialog_ui_ptr_->shader_list->setCurrentRow(0);
	
	connect(&list_dialog_, &QDialog::accepted, [this]() {
		setText(dialog_ui_ptr_->shader_list->selectedItems().front()->text());
	});
	connect(&list_dialog_, &QDialog::rejected, [this]() {
		SetCurrent(text());
	});
	connect(dialog_ui_ptr_->shader_list, &QListWidget::doubleClicked, [this](const QModelIndex& index) {
		setText(index.data().toString());
	});

	AddItems(values);
}

GSelector::~GSelector() = default;

void GSelector::SetList(const QStringList& values)
{
	ClearItems();	
	dialog_ui_ptr_->shader_list->addItems(values);
}

void GSelector::AddItems(const QStringList& values)
{
	dialog_ui_ptr_->shader_list->addItems(values);
}

void GSelector::AddItem(const QString& value)
{
	dialog_ui_ptr_->shader_list->addItem(value);
}

void GSelector::RemoveItem(const QString& value)
{
	QListWidget* list_widget = dialog_ui_ptr_->shader_list;
	auto items = list_widget->findItems(value, Qt::MatchExactly);
	for (auto&& item : items) {	
		dialog_ui_ptr_->shader_list->removeItemWidget(item);		
	}	
}

void GSelector::ClearItems()
{
	dialog_ui_ptr_->shader_list->clear();
	dialog_ui_ptr_->shader_list->addItem("null");
}

void GSelector::SetCurrent(const QString& value)
{
	auto items = dialog_ui_ptr_->shader_list->findItems(value, Qt::MatchExactly);
	dialog_ui_ptr_->shader_list->setCurrentItem(items[0]);
}

void GSelector::SetDialogTitle(const QString& dialog_title)
{
	list_dialog_.setWindowTitle(dialog_title);
}

void GSelector::mouseReleaseEvent(QMouseEvent* event)
{
	QLineEdit::mouseReleaseEvent(event);
	if (event->button() == Qt::LeftButton && geometry().contains(mapToParent(event->pos()))) {			
		list_dialog_.show();	
	}
}
