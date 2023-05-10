#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "Guide.h"
#include "HistoryViewer.h"
#include "UserInfoChanger.h"
#include "Settings.h"
#include "UserInfo.h"
#include "About.h"
#include "DIY.h"
#include "Rank.h"
#include "UserInfo.h"
#include "ui_User.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserClass; };
QT_END_NAMESPACE

class User : public QMainWindow
{
	Q_OBJECT

public:
	User(UserInfo* u, QWidget *parent = nullptr);
	~User();

private slots:
	void view_about();
	void view_rank();
	void export_data();
	void add_content();
	void delete_user();
	void action_settings();
	void info_changer();
	void Start();
	void processRes(int ret);
	void view_history();
	void view_guide();

private:
	Ui::UserClass *ui;
	UserInfo* usr;
	QProcess* process;
	QSqlDatabase database;
};
