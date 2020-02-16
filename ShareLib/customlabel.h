#pragma once

#include <QLabel>

class CustomLabel : public QLabel
{
	Q_OBJECT

public:
	CustomLabel();
	~CustomLabel();

	inline void OnDoubleClick(std::function<void()> eventFunc)
	{
		mOnDoubleClick = eventFunc;
	}
protected:
	std::function<void()> mOnDoubleClick;
	inline void mouseDoubleClickEvent(QMouseEvent *)
	{
		mOnDoubleClick();
	}
};
