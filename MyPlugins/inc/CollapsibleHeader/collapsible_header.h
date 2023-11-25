#pragma once

#include <QtWidgets/QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
	class CollapsibleHeader;
}
QT_END_NAMESPACE

class QParallelAnimationGroup;

class QDESIGNER_WIDGET_EXPORT CollapsibleHeader : public QWidget
{
	Q_OBJECT
	
	Q_PROPERTY(QWidget* ctx	   READ GetPageContent WRITE SetPageContent)
	Q_PROPERTY(QString  header READ GetHeaderText  WRITE SetHeader)
	Q_PROPERTY(QIcon    icon   READ GetIcon        WRITE SetIcon)
public:
	explicit CollapsibleHeader(QWidget* parent = nullptr);
	CollapsibleHeader(const QString& header, QWidget* ctx, QWidget* parent = nullptr);
	~CollapsibleHeader();
	
	void SetHeader(const QString& text);
	void SetIcon(const QIcon& icon);
	void SetPageContent(QWidget* widget_page);
	
	QString  GetHeaderText() const;
	QIcon    GetIcon() const;
	QWidget* GetPageContent();
protected:
	void ChangePageStatus();
	void ResetAnimationBind();

	void resizeEvent(QResizeEvent* event) override;

private:
	void SetCollapsingAnimValue();
	inline void NotifyFinished() { is_anim_finished_ = true; }

private:
	Ui::CollapsibleHeader*   ui_ptr_;
	QParallelAnimationGroup* anim_group_;

	int32_t		 is_collapsing_    : 1 = false;
	int32_t		 is_anim_finished_ : 1 = true;
};