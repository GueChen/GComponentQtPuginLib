#include "ColorCanvas/color_canvas.h"

#include "ui_color_display.h"

#include <QtGui/QPixMap>
#include <QtGui/QResizeEvent>
#include <QtGui/QHoverEvent>
#include <QtGui/QMouseEvent>

constexpr const unsigned int kRgbMask   =  0x00ffffff;
constexpr const unsigned int kAlphaMask =  0xff000000;

ColorCanvas::ColorCanvas(QWidget* parent, QColor color):
	QLabel(parent),	
	display_ptr_(new Ui::DisplayColor)
{	
	setAttribute(Qt::WA_Hover, true);
	installEventFilter(this);

	frame_.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	display_ptr_->setupUi(&frame_);

	SetColor(color);

	connect(&selector_, &QColorDialog::currentColorChanged, this, &ColorCanvas::SetRGB);	
}

ColorCanvas::~ColorCanvas() {
	delete display_ptr_;
}

void ColorCanvas::SetColor(const QColor& color) {	
	if (color != color_) {
		color_ = color;
		selector_.setCurrentColor(color_);
		ColorChange(color_);
		emit ColorChanged(color);
	}
}

void ColorCanvas::SetRGB(const QColor& color) {
	QRgb rgb = color.rgb();
	if (rgb != color_.rgb()) {
		color_.setRgba((rgb & kRgbMask) | (color_.rgba() & kAlphaMask));
		selector_.setCurrentColor(color_);
		ColorChange(color_);
		emit ColorChanged(color_);
	}
}

bool ColorCanvas::eventFilter(QObject* obj, QEvent* event) {
	switch (event->type()) {
	case QEvent::HoverEnter: {
		QPointF pos = mapToGlobal(static_cast<QHoverEvent*>(event)->position());
		frame_.show();
		frame_.setGeometry(pos.x() + 5, pos.y() + 10, 40, 40);
		break;
	}
	case QEvent::HoverMove: {
		QPointF pos = mapToGlobal(static_cast<QHoverEvent*>(event)->position());
		frame_.setGeometry(pos.x() + 5, pos.y() + 10, 40, 40);
		break;
	}
	case QEvent::HoverLeave:
		frame_.hide();
		break;
	}
	return QLabel::eventFilter(obj, event);
}

void ColorCanvas::resizeEvent(QResizeEvent* event) {
	QPixmap map(event->size());
	map.fill(color_);
	setPixmap(map);
	QLabel::resizeEvent(event);
}

void ColorCanvas::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton && selector_.isHidden()) {
		selector_.show();
	}
}

void ColorCanvas::ColorChange(const QColor& color) {
	QPixmap ori_map(size());
	ori_map.fill(color);
	setPixmap(ori_map);

	QPixmap mini_map(display_ptr_->color_boad->size());
	mini_map.fill(color);
	display_ptr_->color_boad->setPixmap(mini_map);

	display_ptr_->hex_form->setText(color.name(QColor::HexArgb));
	display_ptr_->uint_form->setText(QString("R:%1, G:%2, B:%3, A:%4").
		arg(QString::number(color.red())).
		arg(QString::number(color.green())).
		arg(QString::number(color.blue())).
		arg(QString::number(color.alpha())));
	display_ptr_->float_form->setText(QString("(%1, %2, %3, %4)").
		arg(QString::number(color.redF(),   10, 3)).
		arg(QString::number(color.greenF(), 10, 3)).
		arg(QString::number(color.blueF(),  10, 3)).
		arg(QString::number(color.alphaF(), 10, 3)));
}