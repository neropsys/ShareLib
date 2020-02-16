#pragma once
#include <QThread>
#include <QImage>
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
			emit resultReady(result, mFileName);
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
	void resultReady(const QImage &image, const QString& fileName);
};