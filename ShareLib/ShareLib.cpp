#include "stdafx.h"
#include "ShareLib.h"
#include "imageloadthread.h"
#include "customlabel.h"
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>

#include <QCoreApplication>
ShareLib::ShareLib(QWidget *parent)
	: QMainWindow(parent), 
	mFlowLayout(nullptr), 
	mViewerPath("\"C:/Program Files/Honeyview/Honeyview.exe\""),
	mSettingDialog(new Setting(this, mViewerPath))
{
	ui.setupUi(this);
	mFlowLayout = new FlowLayout(ui.scrollAreaWidgetContents);
	ui.scrollArea->setWidgetResizable(true);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);

	connect(ui.settingBtn, &QPushButton::released, this, [&]()
	{
		mSettingDialog->show();

	});
	mSettingDialog->OnClose([&]()
	{
		if (mSettingDialog->PathSet())
		{
			mViewerPath = mSettingDialog->NewPath();
			mViewerPath.append('\"');
			mViewerPath.push_front('\"');
		}
	});
	ui.pathEdit->OnEditingFInished([&]()
	{
		QString path = ui.pathEdit->text();
		qDeleteAll(ui.scrollAreaWidgetContents->findChildren<QLabel*>(QString(), Qt::FindDirectChildrenOnly));

		QDir dir(path);

		QStringList fileNames = dir.entryList(QStringList() << "*.zip" << "*.ZIP", QDir::Files);

		for each (QString fileName in fileNames)
		{


			ImageLoadThread* workerThread = new ImageLoadThread(path + "/" + fileName, fileName);

			connect(workerThread, &ImageLoadThread::resultReady, this, &ShareLib::SetImage);
			connect(workerThread, &ImageLoadThread::finished, workerThread, &QObject::deleteLater);
			workerThread->start();
		
			

		}
	});
	connect(ui.powerBtn, &QPushButton::clicked, this, [&]()
	{
		qDeleteAll(ui.scrollAreaWidgetContents->findChildren<QLabel*>(QString(), Qt::FindDirectChildrenOnly));
	});

}

void ShareLib::SetImage(const QImage& image, const QString& fileName, const QString& path)
{
	//return;
	//Thumb
	CustomLabel* imageLabel = new CustomLabel;

	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->setToolTip(fileName);
	imageLabel->setBackgroundRole(QPalette::Dark);
	imageLabel->OnDoubleClick([=]()
	{

		QProcess* process = new QProcess();
		QString program(mViewerPath);
		program.push_back(' ');
		program.push_back('\"');
		program.append(path);
		program.push_back('\"');
		process->startDetached(program);
	});
	
	mFlowLayout->addWidget(imageLabel);
}
