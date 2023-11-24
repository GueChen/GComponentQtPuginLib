#pragma once

#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVboxLayout>
#include <QtCore/QParallelAnimationGroup>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT CollapsibleHeader : public QWidget
{
	Q_OBJECT
public:
	explicit CollapsibleHeader(QWidget* parent = nullptr);
	~CollapsibleHeader() = default;
	
	void SetHeader(const QString& text);
	void SetIcon(const QIcon& icon);
	void SetPageContent(QWidget* widget_page);

protected:
	void ChangePageStatus();

	void resizeEvent(QResizeEvent* event) override;

private:
	void SetCollapsingAnimValue();
	inline void NotifyFinished() { is_anim_finished_ = true; }

private:
	QPushButton* button_ = nullptr;
	QWidget*     widget_ = nullptr;
	QVBoxLayout* layout_ = nullptr;
	QParallelAnimationGroup anim_group_;

	int32_t		 is_collapsing_    : 1 = false;
	int32_t		 is_anim_finished_ : 1 = true;
};