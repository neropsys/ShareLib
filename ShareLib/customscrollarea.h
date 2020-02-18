#pragma once

#include <QScrollArea>
#include <QMouseEvent>
class CustomScrollArea : public QScrollArea
{
	Q_OBJECT

public:
	CustomScrollArea(QWidget *parent);
	~CustomScrollArea();


	inline void OnScroll(std::function<void()> eventFunc)
	{
		mOnScroll = eventFunc;
	}
protected:
	std::function<void()> mOnScroll;
	inline void wheelEvent(QMouseEvent *event)
	{
		if (this->rect().contains(event->pos()) && event->type() == QEvent::Scroll)
			mOnScroll();
	}
};
