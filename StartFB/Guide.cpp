#include "Guide.h"

Guide::Guide(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::GuideClass())
{
	ui->setupUi(this);
}

Guide::~Guide()
{
	delete ui;
}
