#include "User.h"

User::User(UserInfo* u, QWidget *parent)
	: usr(u), QMainWindow(parent)
	, ui(new Ui::UserClass())
{
	QIcon icon = QApplication::style()->standardIcon((QStyle::StandardPixmap)0);
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);

	ui->setupUi(this);
	ui->HelloLabel->setText("Hello, " + usr->getInfo("username").toString() + "!");
	connect(ui->action_A, &QAction::triggered, this, &User::view_about);
	connect(ui->action_R, &QAction::triggered, this, &User::view_rank);
	connect(ui->action_E, &QAction::triggered, this, &User::export_data);
	connect(ui->addcontentAction, &QAction::triggered, this, &User::add_content);
	connect(ui->action_X, &QAction::triggered, this, &User::delete_user);
	connect(ui->action_S, &QAction::triggered, this, & User::action_settings);
	connect(ui->action_C, &QAction::triggered, this, &User::info_changer);
	connect(ui->StartpushButton, &QPushButton::clicked, this, &User::Start);
	connect(ui->HistorypushButton, &QPushButton::clicked, this, &User::view_history);
	connect(ui->action_M, &QAction::triggered, this, &User::view_guide);

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
}

User::~User()
{
	database.close();
	delete ui;
}

void User::view_about()
{
	About* w = new About;
	w->show();
}

void User::view_rank()
{
	Rank* w = new Rank;
	w->show();
}

void User::export_data()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Export user data.", QDir::currentPath(), "*.json");
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Cannot export!");
		return;
	}
	QFile::copy("users/" + usr->getInfo("uuid").toString() + ".json", fileName);
	QMessageBox::information(this, "Note", "Export successfully!");
}

void User::add_content()
{
	DIY* w = new DIY;
	w->show();
}

void User::delete_user()
{
	QMessageBox msgBox;
	msgBox.setText("WARNING");
	msgBox.setInformativeText("Are you sure you want to delete all your user data?");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int res = msgBox.exec();
	if (res == QMessageBox::Cancel) {
		QMessageBox::information(this, "WARNING", "Delete canceled.");
		return;
	}
	QFile::remove("users/" + usr->getInfo("uuid").toString() + ".json");
	QFile file("users/list.json");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, "WARNING", "Cannot open list.json!\nThe deletion is not complete!");
	}
	QTextStream stream(&file);
	stream.setEncoding(QStringConverter::Utf8);
	QString str = stream.readAll();
	file.close();
	QJsonParseError jsonError;
	QJsonDocument list = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
	QJsonObject obj = list.object();
	obj.remove(usr->getInfo("username").toString());
	list.setObject(obj);
	file.setFileName("users/list.json");
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::warning(this, "WARNING", "Cannot rewrite list.json\nThe deletion is not complete!");
		return;
	}
	QTextStream writeStream(&file);
	writeStream.setEncoding(QStringConverter::Utf8);
	writeStream << list.toJson();
	file.close();
	QMessageBox::information(this, "Note", "Your user data has been deleted!");
	this->close();
}

void User::action_settings()
{
	Settings* w = new Settings(usr);
	w->show();
}

void User::info_changer()
{
	UserInfoChanger* w = new UserInfoChanger(usr);
	w->show();
}

void User::Start() {
	QJsonObject pass;
	pass.insert("lang", "en_us");
	pass.insert("bird", usr->getInfo("bird").toString());
	pass.insert("background", usr->getInfo("background").toString());
	pass.insert("ground", usr->getInfo("ground").toString());
	pass.insert("pipe", usr->getInfo("pipe").toString());
	pass.insert("bgm.file", usr->getInfo("bgm.file").toString());
	pass.insert("bgm", usr->getInfo("bgm").toBool());
	pass.insert("sound", usr->getInfo("sound").toBool());
	QJsonDocument doc(pass);
	QString fileName = "pass.json";
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::warning(this, "WARNING", "Cannot update pass.json!");
		return;
	}
	QTextStream writeStream(&file);
	writeStream.setEncoding(QStringConverter::Utf8);
	writeStream << doc.toJson();
	process = new QProcess(this);
	process->start("./Flappy_Bird.exe");
	connect(this->process, SIGNAL(finished(int)), this, SLOT(processRes(int)));
}

void User::processRes(int ret)
{
	if (ret != 0) {
		QMessageBox::warning(this, "WARNING", "The game failed to exit normally!");
		return;
	}
	QFile file("result");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, "WARNING", "Result file not found!");
		return;
	}
	int score = file.readAll().toInt();
	QFile::remove("result");
	usr->addHistory(score);
	QIcon icon = QApplication::style()->standardIcon((QStyle::StandardPixmap)9);
	trayIcon->showMessage("Game Over!", QString("You got ") + QString::number(score) + " points!", icon);
	QMessageBox msgBox;
	msgBox.setText("Note");
	msgBox.setInformativeText("Do you want to add this result to the leaderboard?");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int res = msgBox.exec();
	if (res == QMessageBox::Ok) {

		QSqlQuery sql_query(database);
		int max_id = sql_query.size();
		if (!sql_query.exec("select max(id) from leaderboard")) {
			QMessageBox::warning(this, "WARNING", "Unable to query the database!");
			return;
		}
		sql_query.next();
		max_id = sql_query.value(0).toInt();
		QString insert_sql = "insert into leaderboard values (?, ?, ?, ?)";
		sql_query.prepare(insert_sql);
		sql_query.addBindValue(max_id + 1);
		sql_query.addBindValue(usr->getInfo("username").toString());
		sql_query.addBindValue(score);
		sql_query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		if (!sql_query.exec())
			QMessageBox::warning(this, "WARNING", "Could not log into database!");
		else
			QMessageBox::information(this, "Note", "This record has been added to the leaderboard.");
	}
}

void User::view_history()
{
	HistoryViewer* w = new HistoryViewer(usr);
	w->show();
}

void User::view_guide()
{
	Guide* w = new Guide;
	w->show();
}
