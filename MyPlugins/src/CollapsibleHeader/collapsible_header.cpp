#include "CollapsibleHeader/collapsible_header.h"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QResizeEvent>

CollapsibleHeader::CollapsibleHeader(QWidget* parent)
	: QWidget(parent)
{	
	layout_ = new QVBoxLayout(this);
	
	QMargins margin_setting;
	margin_setting.setLeft(0);
	margin_setting.setRight(0);
	margin_setting.setTop(0);
	margin_setting.setBottom(0);

	// layout properties
	layout_->setContentsMargins(margin_setting);
	layout_->setSpacing(0);
	
	// header button
	button_ = new QPushButton("Test", this);
	layout_->addWidget(button_);

	// default context
	if (!widget_)
	{
		widget_ = new QLineEdit("This is Widget");		
	}
	layout_->addWidget(widget_);
		
	QPropertyAnimation* ctx_collapsing_anim = new QPropertyAnimation(widget_, "maximumHeight");
	ctx_collapsing_anim->setDuration(200);
	anim_group_.addAnimation(ctx_collapsing_anim);
	
	QPropertyAnimation* collapsing_anim = new QPropertyAnimation(this, "maximumHeight");
	collapsing_anim->setDuration(200);
	anim_group_.addAnimation(collapsing_anim);
	
	SetCollapsingAnimValue();

	QObject::connect(button_,		&QPushButton::clicked, 
					 this,			&CollapsibleHeader::ChangePageStatus);	
	QObject::connect(&anim_group_,	&QParallelAnimationGroup::finished, 
					 this,		    &CollapsibleHeader::NotifyFinished);
}

void CollapsibleHeader::SetHeader(const QString & text)
{
	button_->setText(text);
}

void CollapsibleHeader::SetIcon(const QIcon& icon)
{
	button_->setIcon(icon);
}

void CollapsibleHeader::SetPageContent(QWidget* widget_page)
{
	if (!widget_page) return;
	if (widget_) {
		layout_->removeWidget(widget_);
		widget_->hide();
		delete widget_;
	}
	
	widget_ = widget_page;
	layout_->addWidget(widget_);

}

void CollapsibleHeader::ChangePageStatus()
{
	if (is_anim_finished_) {	// process anim from original status
		// Control widget Visibility		
		is_anim_finished_ = false;
	}
	else {	// pause then try play anim to opposite direction
		anim_group_.pause();		
	}

	if (!is_collapsing_) {	// set animation play direction
		anim_group_.setDirection(QAbstractAnimation::Backward);		
		is_collapsing_ = true;
		QObject::connect(&anim_group_, &QParallelAnimationGroup::finished, widget_, &QWidget::hide);
	}
	else {
		anim_group_.setDirection(QAbstractAnimation::Forward);		
		is_collapsing_ = false;
		anim_group_.disconnect(widget_);
		widget_->show();
	}
	anim_group_.start();
}

void CollapsibleHeader::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	if (is_anim_finished_) {
		SetCollapsingAnimValue();
	}
}

// no safe checking, careful to use this
void CollapsibleHeader::SetCollapsingAnimValue()
{	
	QPropertyAnimation* ctx_collapsing_anim = dynamic_cast<QPropertyAnimation*>(anim_group_.animationAt(0));
	const QSize ctx_size = widget_->size();	
	ctx_collapsing_anim->setStartValue(0);
	ctx_collapsing_anim->setEndValue(ctx_size.height());

	const QSize self_size = size();
	const QSize button_size = button_->size();
	QPropertyAnimation* collapsing_anim = dynamic_cast<QPropertyAnimation*>(anim_group_.animationAt(1));	
	collapsing_anim->setStartValue(button_size.height());
	collapsing_anim->setEndValue(button_size.height() + ctx_size.height() + layout_->spacing());
}
