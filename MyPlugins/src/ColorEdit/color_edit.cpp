#include "ColorEdit/color_edit.h"

#include "ui_color_edit.h"

#include <iostream>

ColorEdit::ColorEdit(QWidget* parent, QColor color):
	QWidget(parent),
	ui_ptr_(new Ui::ColorEdit)
{
	ui_ptr_->setupUi(this);
	
	ui_ptr_->red->  setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(120, 0, 0);");
	ui_ptr_->blue-> setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(0, 0, 150);");
	ui_ptr_->green->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(0, 95, 0);");

	ui_ptr_->red->  setAlignment(Qt::AlignCenter);
	ui_ptr_->blue-> setAlignment(Qt::AlignCenter);
	ui_ptr_->green->setAlignment(Qt::AlignCenter);
	ui_ptr_->alpha->setAlignment(Qt::AlignCenter);

	ui_ptr_->red->  SetMinLimit(0.0f);
	ui_ptr_->blue-> SetMinLimit(0.0f);
	ui_ptr_->green->SetMinLimit(0.0f);
	ui_ptr_->alpha->SetMinLimit(0.0f);

	ui_ptr_->red->  SetMaxLimit(1.0f);
	ui_ptr_->blue-> SetMaxLimit(1.0f);
	ui_ptr_->green->SetMaxLimit(1.0f);
	ui_ptr_->alpha->SetMaxLimit(1.0f);

	ui_ptr_->red->  SetStep(0.005f);
	ui_ptr_->blue-> SetStep(0.005f);
	ui_ptr_->green->SetStep(0.005f);
	ui_ptr_->alpha->SetStep(0.005f);

	SetColor(color);

	connect(ui_ptr_->canvas, &ColorCanvas::ColorChanged, this, &ColorEdit::SetColor);
	connect(ui_ptr_->red,    &DragEdit::ValueChanged,	 this, &ColorEdit::SetRed);
	connect(ui_ptr_->green,	 &DragEdit::ValueChanged,	 this, &ColorEdit::SetGreen);
	connect(ui_ptr_->blue,   &DragEdit::ValueChanged,	 this, &ColorEdit::SetBlue);
	connect(ui_ptr_->alpha,  &DragEdit::ValueChanged,	 this, &ColorEdit::SetAlpha);
}

ColorEdit::~ColorEdit() {
	delete ui_ptr_;
}

void ColorEdit::SetColor(const QColor& color) {
	if (color != color_) {
		color_ = color;

		ui_ptr_->red->  SetValue(color.redF());		
		ui_ptr_->blue-> SetValue(color.blueF());
		ui_ptr_->green->SetValue(color.greenF());
		ui_ptr_->alpha->SetValue(color.alphaF());

		ui_ptr_->canvas->SetColor(color);

		emit ColorChanged(color_);
	}
}

void ColorEdit::SetRed(float red_val) {
	QColor color = color_;
	color.setRedF(red_val);
	SetColor(color);
}

void ColorEdit::SetBlue(float blue_val) {
	QColor color = color_;
	color.setBlueF(blue_val);
	SetColor(color);
}

void ColorEdit::SetGreen(float green_val) {
	QColor color = color_;
	color.setGreenF(green_val);
	SetColor(color);
}

void ColorEdit::SetAlpha(float alpha_val) {
	QColor color = color_;
	color.setAlphaF(alpha_val);
	SetColor(color);
}