#pragma once
#include <QThread>
class ImageLoadThread : public QThread
{
	Q_OBJECT
		void run() override
	{
		QImage result(mPath);
		/* ... here is the expensive or blocking operation ... */
		emit resultReady(result, mFileName);
	}
public:
	ImageLoadThread(const QString& path, const QString& fileName):
		mPath(path),
		mFileName(fileName)
	{}
private:
	QString mPath;
	QString mFileName;
signals:
	void resultReady(const QImage &image, const QString& fileName);
};