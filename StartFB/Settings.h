#pragma once

#include <QWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QMessageBox>
#include <QJsonObject>
#include <QImage>
#include <QButtonGroup>
#include <QFile>
#include "UserInfo.h"
#include "ui_Settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsClass; };
QT_END_NAMESPACE

class Settings : public QWidget
{
	Q_OBJECT

public:
	Settings(UserInfo *u, QWidget *parent = nullptr);
	~Settings();

private slots:
	void reset();
	void reset_default();
	void confirm();
	void set_classic();
	void set_angrybird();
	void set_ironman();
	void set_minecraft();
	void set_unknown();

private:
	void update_box(QString bd, QString bg, QString gd, QString pp, QString bgm);
	Ui::SettingsClass *ui;
	UserInfo* usr;
	QJsonObject resources;
	QJsonParseError jsonError;
};
