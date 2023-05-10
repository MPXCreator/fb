#pragma once
#include <QString>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QMessageBox>
#include <QVector>
#include <QDateTime>

struct record {
	QString time;
	int score;
};

class UserInfo
{
private:
	QJsonObject data;
	QJsonDocument list;
	QJsonParseError jsonError;
public:
	bool good;
	UserInfo(QJsonObject x);
	UserInfo(QString un, QString pwd);
	void update_profile();
	void change_username(QString un);
	void change_password(QString past, QString now);
	QString Calc_SHA256(QString pwd);
	void settings(QString key, QString val);
	void switcher(QString key, bool val);
	QJsonValue getInfo(QString key);
	void read_list();
	QVector<record> getHistory();
	void addHistory(int score);
	void clearHistory();
};