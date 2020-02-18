#pragma once

#include <QLineEdit>
#include <functional>
class ClickEventLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	ClickEventLineEdit(QWidget *parent);
	~ClickEventLineEdit();
	inline void OnEditingFInished(std::function<void()> eventFunc)
	{
		mOnEditFinished = eventFunc;
	}
protected:
	std::function<void()> mOnEditFinished;
	void doubleClicked();

	void mouseDoubleClickEvent(QMouseEvent *)
	{
		doubleClicked();
	}
};
