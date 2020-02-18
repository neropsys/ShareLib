#pragma once
#include <QThread>
#include <QPixmap>
#include <QImageReader>
//#include <QQuickAsyncImageProvider>
#include "quazip/quazipfile.h"
class ImageLoadThread : public QThread
{
	Q_OBJECT
		void run() override
	{
		bool isLoaded = false;

		if (!mZip.open(QuaZip::mdUnzip))
		{
			return;
		}

		mZip.goToFirstFile();
		QuaZipFileInfo64 info;
		mZip.getCurrentFileInfo(&info);
		if (info.isEncrypted())
		{
			return;
		}
		QString firstFileName = mZip.getCurrentFileName();

		QImage result;



		if (firstFileName.contains(".png") ||
			firstFileName.contains(".jpg") ||
			firstFileName.contains(".PNG") ||
			firstFileName.contains(".JPG"))
		{
			QuaZipFile firstFIle(&mZip);
			QImageReader reader;
			reader.setDevice(&firstFIle);
			
			if(reader.canRead())
			{
				reader.setScaledSize(QSize(355, 500));

				result = reader.read();
				isLoaded = true;
			}
			firstFIle.close();
		}

		if (isLoaded)
		{
			emit resultReady(result, mFileName, mPath);
		}
	}
public:
	ImageLoadThread(const QString& path, const QString& fileName):
		mPath(path),
		mFileName(fileName),
		mZip(path)
	{}
	~ImageLoadThread()
	{
		mZip.close();
	}
private:
	QString mPath;
	QString mFileName;
	QuaZip mZip;
signals:
	void resultReady(const QImage &image, const QString& fileName, const QString& path);
};


class ImageLoadWorker : public QObject
{
	Q_OBJECT
public:
	ImageLoadWorker(const QString& path, const QString& fileName):
		mPath(path),
		mFileName(fileName),
		mZip(path)
	{}
	~ImageLoadWorker()
	{
		mZip.close();
	}
public slots:
	void doWork()
	{
		bool isLoaded = false;
		if (!mZip.open(QuaZip::mdUnzip))
		{
			return;
		}

		mZip.goToFirstFile();
		QuaZipFileInfo64 info;
		mZip.getCurrentFileInfo(&info);
		if (info.isEncrypted())
		{
			return;
		}
		QString firstFileName = mZip.getCurrentFileName();
		QImage result;
		if (firstFileName.contains(".png") ||
			firstFileName.contains(".jpg") ||
			firstFileName.contains(".PNG") ||
			firstFileName.contains(".JPG"))
		{
			QuaZipFile firstFIle(&mZip);
			if (firstFIle.open(QIODevice::ReadOnly))
			{

				QByteArray originalData = firstFIle.readAll();

				result.loadFromData(originalData, firstFileName.right(3).toStdString().c_str());
				isLoaded = true;
			}
			firstFIle.close();
		}

		if (isLoaded)
		{
			emit resultReady(result, mFileName, mPath);
		}
	}
private:
	QString mPath;
	QString mFileName;
	QuaZip mZip;

signals:
	void resultReady(const QImage &image, const QString& fileName, const QString& path);
};
// 
// class Controller : public QObject
// {
// 	Q_OBJECT
// 		QThread workerThread;
// public:
// 	Controller()
// 	{
// 		ImageLoadWorker *worker = new ImageLoadWorker;
// 		worker->moveToThread(&workerThread);
// 		connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
// 		connect(this, &Controller::operate, worker, &ImageLoadWorker::doWork);
// 		connect(worker, &ImageLoadWorker::resultReady, this, &Controller::handleResults);
// 		workerThread.start();
// 	}
// 	~Controller()
// 	{
// 		workerThread.quit();
// 		workerThread.wait();
// 	}
// public slots:
// 	void handleResults(const QString &);
// signals:
// 	void operate(const QString &);
// };