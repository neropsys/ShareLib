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
	inline const QString& GetPath()const
	{
		return mSelectedPath;
	}
protected:
	QString mSelectedPath;
	std::function<void()> mOnEditFinished;
	void doubleClicked();

	void mouseDoubleClickEvent(QMouseEvent *)
	{
		doubleClicked();
	}
};
