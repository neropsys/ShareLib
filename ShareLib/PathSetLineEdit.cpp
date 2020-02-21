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
		this->setText(QFileDialog::getExistingDirectory(this, tr("��μ���")));
	}
	else
	{
		this->setText(QFileDialog::getOpenFileName(this, tr("���ϼ���"),"", tr("exe(*.exe)")));
	}
	mOnEditFinished();
}

