#include "stdafx.h"
#include "clickeventlineedit.h"

ClickEventLineEdit::ClickEventLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
}

ClickEventLineEdit::~ClickEventLineEdit()
{
}

void ClickEventLineEdit::doubleClicked()
{
	mOnEditFinished();
}

