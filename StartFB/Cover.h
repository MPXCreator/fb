#pragma once

#include <QWidget>
#include "ui_Cover.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CoverClass; };
QT_END_NAMESPACE

class Cover : public QWidget
{
	Q_OBJECT

public:
	Cover(QWidget *parent = nullptr);
	~Cover();

private:
	Ui::CoverClass *ui;
};
