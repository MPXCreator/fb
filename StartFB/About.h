#pragma once

#include <QMainWindow>
#include <QPixmap>
#include <QDesktopServices>
#include "ui_About.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AboutClass; };
QT_END_NAMESPACE

class About : public QMainWindow
{
	Q_OBJECT

public:
	About(QWidget *parent = nullptr);
	~About();

private slots:
	void Confirm();
	void GitHub();

private:
	Ui::AboutClass *ui;
};
