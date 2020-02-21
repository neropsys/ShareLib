#include "Setting.h"

#include <QCoreApplication>

Setting::Setting(QWidget *parent, const QString& path)
	: QDialog(parent),
	mImageViewerPath(path)
{
	ui.setupUi(this);
	ui.lineEdit->OnEditingFInished([&]()
	{
		QString path = ui.lineEdit->text();
		if (!path.isEmpty())
		{
			mImageViewerPath = path;
			mPathSet = true;
		}
	});
}

Setting::~Setting()
{
}

void Setting::show()
{
	mPathSet = false;
	QDialog::show();
}

void Setting::closeEvent(QCloseEvent *event)
{
	mOnClose();
	QDialog::closeEvent(event);
}