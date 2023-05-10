#pragma once

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QMessageBox>
#include "ui_DIY.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DIYClass; };
QT_END_NAMESPACE

class DIY : public QWidget
{
	Q_OBJECT

public:
	DIY(QWidget *parent = nullptr);
	~DIY();

private slots:
	void BirdFile1_slot();
	void BirdFile2_slot();
	void BirdFile3_slot();
	void BackgroundFile_slot();
	void GroundFile_slot();
	void PipeFile_slot();
	void BGMFile_slot();
	void BirdClear();
	void BackgroundClear();
	void GroundClear();
	void PipeClear();
	void BGMClear();
	void BirdCommit();
	void BackgroundCommit();
	void GroundCommit();
	void PipeCommit();
	void BGMCommit();

private:
	Ui::DIYClass *ui;
	QJsonObject resources;
	QJsonParseError jsonError;
	void update();
};
