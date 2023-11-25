#include "Vector3Edit/vector3_edit.h"

#include "ui_vector3_edit.h"

Vector3Edit::Vector3Edit(QWidget* parent, QVector3D vector):
	QWidget(parent),	
	ui_ptr_(new Ui::Vector3Edit)
{
	ui_ptr_->setupUi(this);

	SetValue(vector);

	connect(ui_ptr_->x, &DragEdit::ValueChanged, this, &Vector3Edit::SetX);
	connect(ui_ptr_->y, &DragEdit::ValueChanged, this, &Vector3Edit::SetY);
	connect(ui_ptr_->z, &DragEdit::ValueChanged, this, &Vector3Edit::SetZ);
}

Vector3Edit::~Vector3Edit()
{}

void Vector3Edit::SetValue(const QVector3D& value) {
	if (vector_ != value) {

		vector_ = value;

		ui_ptr_->x->SetValue(vector_[0]);
		ui_ptr_->y->SetValue(vector_[1]);
		ui_ptr_->z->SetValue(vector_[2]);

		emit VectorChanged(vector_);
	}
}

void Vector3Edit::SetX(float val) {
	if (val == vector_[0] || std::isnan(val)) return;
	vector_[0] = val;

	ui_ptr_->x->SetValue(val);

	emit VectorChanged(vector_);
}

void Vector3Edit::SetY(float val) {
	if (val == vector_[1] || std::isnan(val)) return;
	vector_[1] = val;

	ui_ptr_->y->SetValue(val);

	emit VectorChanged(vector_);
}

void Vector3Edit::SetZ(float val) {
	if (val == vector_[2] || std::isnan(val)) return;
	vector_[2] = val;

	ui_ptr_->z->SetValue(val);

	emit VectorChanged(vector_);
}

void Vector3Edit::SetXRange(float lower, float upper) {
	assert(lower <= upper && "lower should be less than upper");
	ui_ptr_->x->SetMaxLimit(upper);
	ui_ptr_->x->SetMinLimit(lower);
}

void Vector3Edit::SetYRange(float lower, float upper) {
	assert(lower <= upper && "lower should be less than upper");
	ui_ptr_->y->SetMaxLimit(upper);
	ui_ptr_->y->SetMinLimit(lower);
}

void Vector3Edit::SetZRange(float lower, float upper) {
	assert(lower <= upper && "lower should be less than upper");
	ui_ptr_->z->SetMaxLimit(upper);
	ui_ptr_->z->SetMinLimit(lower);
}

void Vector3Edit::SetRange(float lower, float upper) {
	SetXRange(lower, upper);
	SetYRange(lower, upper);
	SetZRange(lower, upper);
}

void Vector3Edit::SetStep(float step) {
	ui_ptr_->x->SetStep(step);
	ui_ptr_->y->SetStep(step);
	ui_ptr_->z->SetStep(step);
}