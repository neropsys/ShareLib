#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ShareLib.h"
#include "Setting.h"
#include "flowlayout.h"
#include <QVector>
class ShareLib : public QMainWindow
{
	Q_OBJECT

public:
	ShareLib(QWidget *parent = Q_NULLPTR);

private:
	QString mViewerPath;
	QVector<QWidget*> imageList;
	Ui::ShareLibClass ui;
	FlowLayout* mFlowLayout = nullptr;
	Setting* mSettingDialog = nullptr;
	void SetImage(const QImage& image, const QString& fileName, const QString& path);
};
