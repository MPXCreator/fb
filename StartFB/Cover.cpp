#include "Cover.h"

Cover::Cover(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CoverClass())
{
	ui->setupUi(this);
}

Cover::~Cover()
{
	delete ui;
}
