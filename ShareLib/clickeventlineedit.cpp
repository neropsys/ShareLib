#include "stdafx.h"
#include "clickeventlineedit.h"
#include <QFileDialog>
ClickEventLineEdit::ClickEventLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
}

ClickEventLineEdit::~ClickEventLineEdit()
{
}

void ClickEventLineEdit::doubleClicked()
{
	auto fileName = QFileDialog::getExistingDirectory(this, "��μ���");
	this->setText(fileName);
	mOnEditFinished();
}

