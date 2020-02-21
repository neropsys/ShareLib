#pragma once

#include <QWidget>
#include <functional>
#include "ui_Setting.h"
class Setting : public QDialog
{
	Q_OBJECT

public:
	Setting(QWidget *parent, const QString& path);
	~Setting();
	inline void OnClose(std::function<void()> eventFunc)
	{
		mOnClose = eventFunc;
	}
	inline const QString& NewPath() const
	{
		return mImageViewerPath;
	}
	inline bool PathSet() const
	{
		return mPathSet;
	}
	void show();
protected:
	void closeEvent(QCloseEvent *event);
	
private:
	Setting();
	bool mPathSet = false;
	std::function<void()> mOnClose;
	QString mImageViewerPath;
	Ui::Dialog ui;
};
