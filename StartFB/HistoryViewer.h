#pragma once

#include <QWidget>
#include "UserInfo.h"
#include "ui_HistoryViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HistoryViewerClass; };
QT_END_NAMESPACE

class HistoryViewer : public QWidget
{
	Q_OBJECT

public:
	HistoryViewer(UserInfo* u, QWidget *parent = nullptr);
	~HistoryViewer();

private slots:
	void clear();

private:
	Ui::HistoryViewerClass *ui;
	UserInfo* usr;
	void update_table();
};
