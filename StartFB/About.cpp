#include "About.h"

About::About(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::AboutClass())
{
	ui->setupUi(this);

	QPixmap* pixmap = new QPixmap("resources/icon.png");
	pixmap->scaled(ui->Iconlabel->size(), Qt::KeepAspectRatio);
	ui->Iconlabel->setScaledContents(true);
	ui->Iconlabel->setPixmap(*pixmap);

	connect(ui->ConfirmpushButton, &QPushButton::clicked, this, &About::Confirm);
	connect(ui->GitHubpushButton, &QPushButton::clicked, this, &About::GitHub);

	ui->Versionlabel->setText("Version: Beta v0.1.1");
	ui->Versionlabel->setAlignment(Qt::AlignRight);
}

About::~About()
{
	delete ui;
}

void About::Confirm() {
	this->close();
}

void About::GitHub() {
	QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/MPXCreator/fb")));
}