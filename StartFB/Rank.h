#pragma once

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVector>
#include <algorithm>
#include "ui_Rank.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RankClass; };
QT_END_NAMESPACE

class Rank : public QWidget
{
	Q_OBJECT

public:
	Rank(QWidget *parent = nullptr);
	~Rank();

private slots:
	void search();
	void update_table(QString x);

private:
	QSqlDatabase database;
	Ui::RankClass *ui;
};
