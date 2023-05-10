#pragma once

#include <QWidget>
#include "ui_Guide.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GuideClass; };
QT_END_NAMESPACE

class Guide : public QWidget
{
	Q_OBJECT

public:
	Guide(QWidget *parent = nullptr);
	~Guide();

private:
	Ui::GuideClass *ui;
};
