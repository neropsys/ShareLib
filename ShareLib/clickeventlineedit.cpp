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
	auto fileName = QFileDialog::getExistingDirectory(this, "경로선택");
	this->setText(fileName);
	mOnEditFinished();
}

