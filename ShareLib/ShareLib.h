#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ShareLib.h"

#include "flowlayout.h"
#include <QVector>
class ShareLib : public QMainWindow
{
	Q_OBJECT

public:
	ShareLib(QWidget *parent = Q_NULLPTR);

private:
	QVector<QWidget*> imageList;
	Ui::ShareLibClass ui;
	FlowLayout* mFlowLayout=nullptr;
	void SetImage(const QImage& image, const QString& fileName);
};
