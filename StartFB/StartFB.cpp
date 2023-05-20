#include "StartFB.h"

StartFB::StartFB(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartFBClass())
{
    ui->setupUi(this);
    ui->PasswordlineEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
    connect(ui->ClearpushButton, &QPushButton::clicked, this, &StartFB::clear_button_clicked);
    connect(ui->action_S, &QAction::triggered, this, &StartFB::signup);
    connect(ui->action_I, &QAction::triggered, this, &StartFB::import_user);
    connect(ui->action_E, &QAction::triggered, this, &StartFB::export_user);
    connect(ui->action_R, &QAction::triggered, this, &StartFB::view_rank);
    connect(ui->action, &QAction::triggered, this, &StartFB::view_about);
    connect(ui->LoginpushButton, &QPushButton::clicked, this, &StartFB::login);
    connect(ui->action_M, &QAction::triggered, this, &StartFB::view_guide);
    connect(ui->action_V, &QAction::triggered, this, &StartFB::visitor);

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
        QMessageBox::warning(this, "WARNING", "Cannot open the database.");
    else {
        QSqlQuery sqlQuery;
        sqlQuery.exec("SELECT * FROM leaderboard");
        if (!sqlQuery.exec()) {
            QMessageBox::warning(this, "WARNING", "Cannot find the table from the database.\nCreating...");
            sqlQuery.prepare("CREATE TABLE leaderboard (\
                          id INT PRIMARY KEY NOT NULL,\
                          name TEXT NOT NULL,\
                          score INT NOT NULL,\
                          time TEXT NOT NULL)");
            if (!sqlQuery.exec())
                QMessageBox::warning(this, "WARNING", "Cannot create the table!");
        }
    }

}

void StartFB::clear_button_clicked() {
    ui->UsernamelineEdit->setText("");
    ui->PasswordlineEdit->setText("");
}

void StartFB::signup() {
    read_list();
    Signup* w = new Signup(list);
    w->show();
}

void StartFB::import_user()
{
    read_list();
    QString fileName = QFileDialog::getOpenFileName(this, "Import user data.", QDir::currentPath(), "*.json");
    if (fileName.isEmpty())
        QMessageBox::warning(this, "WARNING", "Cannot open the file.");
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "WARNING", "Could not open the specified file.");
        return;
    }
    QJsonDocument doc;
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    QString str = stream.readAll();
    file.close();
    doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        QMessageBox::warning(this, "WARNING", "The imported file is abnormal.");
        return;
    }
    QJsonObject obj = doc.object();
    if (!(obj.contains("username") && obj.contains("password") && obj.contains("uuid")
        && obj.contains("best") && obj.contains("best") && obj.contains("bird")
        && obj.contains("background") && obj.contains("ground") && obj.contains("sound")
        && obj.contains("sound") && obj.contains("pipe") && obj.contains("bgm") && obj.contains("bgm.file")
        && obj.contains("history"))) {
        QMessageBox::warning(this, "WARNING", "The imported file is incomplete!");
        return;
    }
    QJsonObject exist = list.object();
    if (exist.contains(obj["username"].toString())) {
        QMessageBox::warning(this, "WARNING", "Username already exists!");
        return;
    }
    QUuid id = QUuid::createUuid();
    obj["uuid"] = id.toString();

    exist.insert(obj["username"].toString(), id.toString());
    list.setObject(exist);
    if (!update_list()) {
        exist.remove(obj["username"].toString());
        list.setObject(exist);
        QMessageBox::warning(this, "WARNING", "Import failed!");
        return;
    }

    QFile ufile("users/" + id.toString() + ".json");
    if (!ufile.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(this, "WARNING", "Cannot update users/list.json");
    }
    QTextStream writeStream(&ufile);
    writeStream.setEncoding(QStringConverter::Utf8);
    doc.setObject(obj);
    writeStream << doc.toJson();
    ufile.close();

    QMessageBox::information(this, "Note", "User data imported successfully.");
}

void StartFB::export_user()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export user data.", QDir::currentPath(), ".*json");
    if (fileName.isEmpty())
        QMessageBox::warning(this, "WARNING", "Cannot export!");
    QMessageBox::warning(this, "WARNING", "Please log in and try.");
}

void StartFB::view_rank()
{
    Rank* w = new Rank;
    w->show();
}

void StartFB::view_about()
{
    About *w = new About;
    w->show();
}

void StartFB::login()
{
    QString un = ui->UsernamelineEdit->text(),
        pwd = ui->PasswordlineEdit->text();
    UserInfo* usr = new UserInfo(un, pwd);
    if (!usr->good) {
        delete usr;
        return;
    }
    User* w = new User(usr);
    w->show();
    this->hide();
}

void StartFB::view_guide()
{
    Guide* w = new Guide;
    w->show();
}

void StartFB::read_list()
{
    QFile file("users/list.json");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "WARNING", "Cannot open list.json!\nCreating one...");
        QFile creator("users/list.json");
        creator.open(QFile::WriteOnly);
        creator.write(QString("{}").toUtf8());
        creator.close();
        file.open(QFile::ReadOnly | QFile::Text);
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    QString str = stream.readAll();
    list = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        QMessageBox::warning(this, "WARNING", "Json Parse error, please delete users/list.json and retry.");
        this->close();
        return;
    }
}

bool StartFB::update_list()
{
    QFile file("users/list.json");
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(this, "WARNING", "Cannot update users/list.json");
        return false;
    }
    QTextStream writeStream(&file);
    writeStream.setEncoding(QStringConverter::Utf8);
    writeStream << list.toJson();
    return true;
}

void StartFB::visitor() {
    QMessageBox::warning(this, "Yahaha!", "Please register to play!");
}

StartFB::~StartFB()
{
    database.close();
    delete ui;
}
