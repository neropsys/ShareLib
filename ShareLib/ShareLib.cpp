#include "stdafx.h"
#include "ShareLib.h"
#include "imageloadthread.h"
ShareLib::ShareLib(QWidget *parent)
	: QMainWindow(parent), mFlowLayout(nullptr)
{
	ui.setupUi(this);
	mFlowLayout = new FlowLayout(ui.scrollAreaWidgetContents);
	ui.scrollArea->setWidgetResizable(true);
	ui.pathEdit->OnEditingFInished([&]()
	{
		QString path = ui.pathEdit->text();
		QDir dir(path);

		QStringList images = dir.entryList(QStringList() << "*.jpg" << "*.png" << "*.PNG" << "*.JPG", QDir::Files);
		ui.scrollArea->setBackgroundRole(QPalette::Dark);
		for each (QString fileName in images)
		{
			ImageLoadThread* workerThread = new ImageLoadThread(path + "/" + fileName, fileName);

			connect(workerThread, &ImageLoadThread::resultReady, this, &ShareLib::SetImage);
			connect(workerThread, &ImageLoadThread::finished, workerThread, &QObject::deleteLater);
			workerThread->start();
			
		}
		

		
	});
}

void ShareLib::SetImage(const QImage& image, const QString& fileName)
{
	QLabel* imageLabel = new QLabel;

	imageLabel->setPixmap(QPixmap::fromImage(image).scaled(QSize(355, 500), Qt::IgnoreAspectRatio));
	imageLabel->setToolTip(fileName);
	imageLabel->setMinimumSize(QSize(355, 500));
	imageLabel->setMaximumSize(QSize(355, 500));
	imageLabel->setBackgroundRole(QPalette::Dark);
	mFlowLayout->addWidget(imageLabel);
}
