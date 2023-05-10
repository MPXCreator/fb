#pragma once

#include <QWidget>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QUuid>
#include "ui_Signup.h"
#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class SignupClass; };
QT_END_NAMESPACE

class Signup : public QWidget
{
	Q_OBJECT

public:
	Signup(QJsonDocument l, QWidget *parent = nullptr);
	~Signup();

private:
	Ui::SignupClass *ui;
	QString Calc_SHA256(QString pwd);
	QJsonDocument list;
	QJsonParseError jsonError;
	void clear_button_clicked();
	void signup_button_clicked();
};
