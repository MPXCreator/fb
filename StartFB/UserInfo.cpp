#include "UserInfo.h"

UserInfo::UserInfo(QJsonObject x)
{
    data = x;
    good = true;
}

UserInfo::UserInfo(QString un, QString pwd) {
    good = false;
    read_list();
    QJsonObject obj = list.object();
    if (!obj.contains(un)) {
        QMessageBox::warning(NULL, "WARNING", "Username does not exist!");
        return;
    }
    QFile file("users/" + obj[un].toString() + ".json");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(NULL, "WARNING", "Cannot open the user's profile!");
        return;
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    QString str = stream.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        QMessageBox::warning(NULL, "WARNING", "Json Parse error!");
        return;
    }
    data = doc.object();
    if (data["password"] != Calc_SHA256(pwd)) {
        QMessageBox::warning(NULL, "WARNING", "Wrong password!");
        return;
    }
    good = true;
}

void UserInfo::update_profile()
{
	QString fileName = "users/" + data["uuid"].toString() + ".json";
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::warning(NULL, "WARNING", "Cannot update user's profile!");
		return;
	}
	QTextStream writeStream(&file);
	writeStream.setEncoding(QStringConverter::Utf8);
	QJsonDocument doc(data);
	writeStream << doc.toJson();
}

void UserInfo::change_password(QString past, QString now)
{
    past = Calc_SHA256(past);
    now = Calc_SHA256(now);
    if (past != data["password"].toString()) {
        QMessageBox::warning(NULL, "WARNING", "Past password does not match!");
        return;
    }
    data["password"] = now;
    update_profile();
    QMessageBox::information(NULL, "Note", "The password has been changed!");
}

QString UserInfo::Calc_SHA256(QString pwd)
{
	QByteArray byteArray(pwd.toUtf8());
	QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha3_256);
	return hash.toHex();
}

void UserInfo::settings(QString key, QString val)
{
    data[key] = val;
    update_profile();
}

void UserInfo::switcher(QString key, bool val)
{
    data[key] = val;
    update_profile();
}

QJsonValue UserInfo::getInfo(QString key)
{
    return data[key];
}

void UserInfo::read_list()
{
    QFile file("users/list.json");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(NULL, "WARNING", "Cannot open list.json!\nCreating one...");
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
        QMessageBox::warning(NULL, "WARNING", "Json Parse error, please delete users/list.json and retry.");
        return;
    }
}

QVector<record> UserInfo::getHistory()
{
    QJsonArray x = data["history"].toArray();
    QVector<record> res;
    record rec;
    for (auto i : x) {
        QString tmp = i.toString();
        QStringList lst = tmp.split(',');
        rec.time = lst.at(0);
        rec.score = lst.at(1).toInt();
        res.append(rec);
    }
    return res;
}

void UserInfo::addHistory(int score)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString str = dateTime.toString("yyyy-MM-dd/hh:mm:ss");
    QJsonArray arr = data["history"].toArray();
    arr.push_front(str + "," + QString::number(score));
    data["history"] = arr;
    update_profile();
}

void UserInfo::clearHistory()
{
    QJsonArray tmp;
    data["history"] = tmp;
}

void UserInfo::change_username(QString un)
{
    QJsonObject obj = list.object();
    if (obj.contains(un)) {
        QMessageBox::warning(NULL, "WARNING", "Username already taken!");
        return;
    }
    obj.remove(data["username"].toString());
    obj.insert(un, data["uuid"].toString());
    data["username"] = un;
    update_profile();
    QString fileName = "users/list.json";
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(NULL, "WARNING", "Cannot update users list!");
        return;
    }
    QTextStream writeStream(&file);
    writeStream.setEncoding(QStringConverter::Utf8);
    list.setObject(obj);
    writeStream << list.toJson();
    QMessageBox::information(NULL, "Note", "Username has been modified!");
}
