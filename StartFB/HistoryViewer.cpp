#include "HistoryViewer.h"

HistoryViewer::HistoryViewer(UserInfo* u, QWidget *parent)
	: usr(u)
	, QWidget(parent)
	, ui(new Ui::HistoryViewerClass())
{
	ui->setupUi(this);
	update_table();
	connect(ui->ClearpushButton, &QPushButton::clicked, this, &HistoryViewer::clear);
}

HistoryViewer::~HistoryViewer()
{
	delete ui;
}

void HistoryViewer::clear() {
	usr->clearHistory();
	ui->tableWidget->clear();
}

void HistoryViewer::update_table()
{
	QVector<record> tmp = usr->getHistory();
	ui->tableWidget->setRowCount(tmp.size());
	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Time" << "Score");
	for (int i = 0; i < tmp.size(); i++) {
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tmp[i].time));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(tmp[i].score)));
	}
}
