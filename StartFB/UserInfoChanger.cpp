#include "UserInfoChanger.h"

UserInfoChanger::UserInfoChanger(UserInfo *u, QWidget *parent)
	: usr(u)
	, QWidget(parent)
	, ui(new Ui::UserInfoChangerClass())
{
	ui->setupUi(this);
	connect(ui->ClearpushButton, &QPushButton::clicked, this, &UserInfoChanger::clear);
	connect(ui->CommitpushButton, &QPushButton::clicked, this, &UserInfoChanger::confirm);
}

UserInfoChanger::~UserInfoChanger()
{
	delete ui;
}

void UserInfoChanger::clear() {
	ui->NamelineEdit->clear();
	ui->PastlineEdit->clear();
	ui->RelineEdit->clear();
}

void UserInfoChanger::confirm() {
	if (!ui->NamelineEdit->text().isEmpty())
		usr->change_username(ui->NamelineEdit->text());
	if (!ui->RelineEdit->text().isEmpty() || !ui->NowlineEdit->text().isEmpty() || !ui->PastlineEdit->text().isEmpty())
	{
		if (ui->RelineEdit->text().isEmpty() || ui->NowlineEdit->text().isEmpty() || ui->PastlineEdit->text().isEmpty()) {
			QMessageBox::warning(this, "WARNING", "If you want to change the password, please do not leave some blank!");
			this->close();
		}
		if (ui->RelineEdit->text() != ui->NowlineEdit->text()) {
			QMessageBox::warning(this, "WARNING", "The passwords entered twice are inconsistent!");
			this->close();
		}
		usr->change_password(ui->PastlineEdit->text(), ui->NowlineEdit->text());
	}
	this->close();
}