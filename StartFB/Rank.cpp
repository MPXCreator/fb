#include "Rank.h"

Rank::Rank(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::RankClass())
{
	ui->setupUi(this);
	
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		database = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName("leaderboard.db");
		database.setUserName("Reyes");
		database.setPassword("9-0w>KPe|c5&$BFbS27*");
	}
	if (!database.open())
		QMessageBox::warning(this, "WARNING", "Cannot open the leaderboard database!");

	update_table("");
	
	connect(ui->pushButton, &QPushButton::clicked, this, &Rank::search);
}

Rank::~Rank()
{
	delete ui;
}

struct archieve {
	QString name, time;
	int score;
};

void Rank::search() {
	update_table(ui->lineEdit->text());
}

void Rank::update_table(QString x) {
	ui->tableWidget->clear();
	QSqlQuery sql_query(database);
	if (!sql_query.exec("select * from leaderboard")) {
		QMessageBox::warning(this, "WARNING", "Unable to query the database!");
		return;
	}
	QVector<archieve> res;
	while (sql_query.next())
		if (x.isEmpty() || sql_query.value(1).toString() == x)
			res.push_back({ sql_query.value(1).toString(), sql_query.value(3).toString(), sql_query.value(2).toInt() });
	std::sort(res.begin(), res.end(), [](archieve a, archieve b) { return a.score > b.score; });
	ui->tableWidget->setColumnCount(3);
	ui->tableWidget->setRowCount(res.size());
	ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Score" << "Time");
	for (int i = 0; i < res.size(); i++) {
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(res[i].name));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(res[i].score)));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(res[i].time));
	}
}
