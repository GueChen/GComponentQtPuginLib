#include "CollapsibleHeader/collapsible_header.h"

#include "ui_collapsible_header.h"

#include <QtWidgets/QVboxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QResizeEvent>

CollapsibleHeader::CollapsibleHeader(QWidget* parent) :
	QWidget(parent),
	ui_ptr_(new Ui::CollapsibleHeader)
{	
	ui_ptr_->setupUi(this);
		
	// header button
	anim_group_ = new QParallelAnimationGroup(this);
		
	ResetAnimationBind();
	
	SetCollapsingAnimValue();

	QObject::connect(ui_ptr_->header,		&QPushButton::clicked, 
					 this,					&CollapsibleHeader::ChangePageStatus);	
	QObject::connect(anim_group_,			&QParallelAnimationGroup::finished, 
					 this,					&CollapsibleHeader::NotifyFinished);
}

CollapsibleHeader::CollapsibleHeader(const QString& header, QWidget* ctx, QWidget* parent) :	
	CollapsibleHeader(parent)
{
	SetHeader(header);
	SetPageContent(ctx);
}

CollapsibleHeader::~CollapsibleHeader()
{
	delete ui_ptr_;
}

void CollapsibleHeader::SetHeader(const QString & text)
{
	ui_ptr_->header->setText(text);
}

void CollapsibleHeader::SetIcon(const QIcon& icon)
{
	ui_ptr_->header->setIcon(icon);
}

void CollapsibleHeader::SetPageContent(QWidget* widget_page)
{
	if (!widget_page) return;
	QWidget*      widget = ui_ptr_->widget;
	QHBoxLayout*  layout = ui_ptr_->ctx_layout;
	layout->removeWidget(widget);
	widget->hide();
	delete widget;
	
	ui_ptr_->widget = widget_page;
	layout->addWidget(widget_page);
	
	ResetAnimationBind();
	SetCollapsingAnimValue();
}

QString CollapsibleHeader::GetHeaderText() const
{
	return ui_ptr_->header->text();
}

QIcon CollapsibleHeader::GetIcon() const
{
	return ui_ptr_->header->icon();
}

QWidget* CollapsibleHeader::GetPageContent()
{
	return ui_ptr_->widget;
}

void CollapsibleHeader::ChangePageStatus()
{
	if (is_anim_finished_) {	// process anim from original status
		// Control widget Visibility		
		is_anim_finished_ = false;
	}
	else {	// pause then try play anim to opposite direction
		anim_group_->pause();		
	}

	if (!is_collapsing_) {	// set animation play direction
		anim_group_->setDirection(QAbstractAnimation::Backward);
		is_collapsing_ = true;
		QObject::connect(anim_group_, &QParallelAnimationGroup::finished, ui_ptr_->widget, &QWidget::hide);
	}
	else {
		anim_group_->setDirection(QAbstractAnimation::Forward);		
		is_collapsing_ = false;
		anim_group_->disconnect(ui_ptr_->widget);
		ui_ptr_->widget->show();
	}
	anim_group_->start();
}

void CollapsibleHeader::ResetAnimationBind()
{
	anim_group_->clear();

	QPropertyAnimation* ctx_collapsing_anim = new QPropertyAnimation(ui_ptr_->widget, "maximumHeight");
	ctx_collapsing_anim->setDuration(300);
	//ctx_collapsing_anim->setEasingCurve(QEasingCurve::InOutQuint);
	anim_group_->addAnimation(ctx_collapsing_anim);

	QPropertyAnimation* collapsing_anim = new QPropertyAnimation(this, "maximumHeight");
	collapsing_anim->setDuration(300);
	//ctx_collapsing_anim->setEasingCurve(QEasingCurve::InOutQuint);
	anim_group_->addAnimation(collapsing_anim);
}

void CollapsibleHeader::resizeEvent(QResizeEvent* event)
{	
	if (QWidget* pw = parentWidget(); pw && dynamic_cast<CollapsibleHeader*>(pw)) {		
		const int32_t max_pheight = pw->maximumHeight();
		const int32_t cur_pheight = pw->height();
		const int32_t inc_height = event->size().height();

		if (max_pheight < cur_pheight + inc_height) {
			pw->setMaximumHeight(max_pheight + inc_height);
		}		
	}

	QWidget::resizeEvent(event);	

	if (is_anim_finished_ && ui_ptr_->widget->height()) {
		SetCollapsingAnimValue();
	}
}

// no safe checking, careful to use this
void CollapsibleHeader::SetCollapsingAnimValue()
{	
	QPropertyAnimation* ctx_collapsing_anim = dynamic_cast<QPropertyAnimation*>(anim_group_->animationAt(0));
	const QSize ctx_size = ui_ptr_->widget->size();	
	ctx_collapsing_anim->setStartValue(0);
	ctx_collapsing_anim->setEndValue(ctx_size.height());

	QVBoxLayout* layout = ui_ptr_->layout;
	const QSize self_size = size();
	const QSize button_size = ui_ptr_->header->size();	
	QPropertyAnimation* collapsing_anim = dynamic_cast<QPropertyAnimation*>(anim_group_->animationAt(1));	
	collapsing_anim->setStartValue(button_size.height());
	collapsing_anim->setEndValue(button_size.height() + ctx_size.height() + layout->spacing());
}
