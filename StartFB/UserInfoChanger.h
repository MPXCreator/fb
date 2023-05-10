#pragma once

#include <QWidget>
#include "UserInfo.h"
#include "ui_UserInfoChanger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserInfoChangerClass; };
QT_END_NAMESPACE

class UserInfoChanger : public QWidget
{
	Q_OBJECT

public:
	UserInfoChanger(UserInfo *u, QWidget *parent = nullptr);
	~UserInfoChanger();

private slots:
	void clear();
	void confirm();

private:
	UserInfo* usr;
	Ui::UserInfoChangerClass *ui;
};
