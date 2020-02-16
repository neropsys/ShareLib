#include "stdafx.h"
#include "ShareLib.h"
#include "imageloadthread.h"
ShareLib::ShareLib(QWidget *parent)
	: QMainWindow(parent), mFlowLayout(nullptr)
{
	ui.setupUi(this);
	mFlowLayout = new FlowLayout(ui.scrollAreaWidgetContents);
	ui.scrollArea->setWidgetResizable(true);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);
	ui.pathEdit->OnEditingFInished([&]()
	{

		qDeleteAll(ui.scrollAreaWidgetContents->findChildren<QLabel*>(QString(), Qt::FindDirectChildrenOnly));

		QString path = ui.pathEdit->text();
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

void ShareLib::SetImage(const QImage& image, const QString& fileName)
{

	//Thumb
	QLabel* imageLabel = new QLabel;

	imageLabel->setPixmap(QPixmap::fromImage(image).scaled(QSize(355, 500), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	imageLabel->setToolTip(fileName);
	imageLabel->setMinimumSize(QSize(355, 500));
	imageLabel->setMaximumSize(QSize(355, 500));
	imageLabel->setBackgroundRole(QPalette::Dark);
	mFlowLayout->addWidget(imageLabel);
	imageList.push_back(imageLabel);
}
