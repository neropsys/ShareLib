#include "stdafx.h"
#include "PathSetLineEdit.h"

PathSetLineEdit::PathSetLineEdit(QWidget *parent, bool fileMode)
	: QLineEdit(parent), mFileMode(fileMode)
{
}

PathSetLineEdit::~PathSetLineEdit()
{
}

void PathSetLineEdit::doubleClicked()
{
	if (mFileMode == false)
	{
		this->setText(QFileDialog::getExistingDirectory(this, tr("경로선택")));
	}
	else
	{
		this->setText(QFileDialog::getOpenFileName(this, tr("파일선택"),"", tr("exe(*.exe)")));
	}
	mOnEditFinished();
}

