#pragma once

#include <QLineEdit>
#include <functional>
class PathSetLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	PathSetLineEdit(QWidget *parent, bool fileMode=false);
	~PathSetLineEdit();
	inline void OnEditingFInished(std::function<void()> eventFunc)
	{
		mOnEditFinished = eventFunc;
	}
protected:
	bool mFileMode = false;
	std::function<void()> mOnEditFinished;
	void doubleClicked();

	void mouseDoubleClickEvent(QMouseEvent *)
	{
		doubleClicked();
	}
};
