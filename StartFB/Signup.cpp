#include "Signup.h"

Signup::Signup(QJsonDocument l, QWidget *parent)
	: list(l)
	,QWidget(parent)
	, ui(new Ui::SignupClass())
{
	ui->setupUi(this);
	ui->pwdLineEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
	ui->reLineEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
	connect(ui->clearPushButton, &QPushButton::clicked, this, &Signup::clear_button_clicked);
	connect(ui->signupPushButton, &QPushButton::clicked, this, &Signup::signup_button_clicked);
}

Signup::~Signup()
{
	delete ui;
}

QString Signup::Calc_SHA256(QString pwd)
{
	QByteArray byteArray(pwd.toUtf8());
	QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha3_256);
	return hash.toHex();
}

void Signup::clear_button_clicked()
{
	ui->nameLineEdit->clear();
	ui->pwdLineEdit->clear();
	ui->reLineEdit->clear();
}

void Signup::signup_button_clicked()
{
	if (ui->nameLineEdit->text().isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Username can not be empty.");
		return;
	}
	QString x = ui->pwdLineEdit->text(), y = ui->reLineEdit->text();
	if (x != y) {
		QMessageBox::warning(this, "WARNING", "Password do not match!");
		clear_button_clicked();
		return;
	}
	x = Calc_SHA256(x);
	QJsonObject tmp = list.object();
	if (tmp.contains(ui->nameLineEdit->text())) {
		QMessageBox::warning(this, "WARNING", "Username already in use.");
		return;
	}
	QUuid id = QUuid::createUuid();
	tmp.insert(ui->nameLineEdit->text(), id.toString());
	QFile file("users/list.json");
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::warning(this, "WARNING", "Cannot open users/list.json!");
		return;
	}
	QTextStream stream(&file);
	stream.setEncoding(QStringConverter::Utf8);
	QJsonDocument doc;
	doc.setObject(tmp);
	stream << doc.toJson();
	file.close();
	QJsonObject userInfo;
	userInfo.insert("username", ui->nameLineEdit->text());
	userInfo.insert("password", x);
	userInfo.insert("uuid", id.toString());
	userInfo.insert("best", 0);
	userInfo.insert("bird", "yellow");
	userInfo.insert("background", "day.png");
	userInfo.insert("ground", "normal.png");
	userInfo.insert("pipe", "green.png");
	userInfo.insert("sound", true);
	userInfo.insert("bgm", false);
	userInfo.insert("bgm.file", "C418 - Cat.flac");
	QJsonArray tmpArray;
	userInfo.insert("history", tmpArray);
	QString filePath = "users/";
	filePath += id.toString() + ".json";
	file.setFileName(filePath);
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::warning(this, "WARNING", "Cannot write user data!");
		return;
	}
	QTextStream writeStream(&file);
	writeStream.setEncoding(QStringConverter::Utf8);
	doc.setObject(userInfo);
	writeStream << doc.toJson();
	file.close();
	QMessageBox::information(this, "Note", "Account has been successfully registered.");
	this->close();
}
