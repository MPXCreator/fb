#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "Guide.h"
#include "User.h"
#include "DIY.h"
#include "Signup.h"
#include "About.h"
#include "Rank.h"
#include "ui_StartFB.h"
#include "UserInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartFBClass; };
QT_END_NAMESPACE

class StartFB : public QMainWindow
{
    Q_OBJECT

public:
    StartFB(QWidget *parent = nullptr);
    ~StartFB();

private slots:
    void clear_button_clicked();
    void signup();
    void import_user();
    void export_user();
    void view_rank();
    void view_about();
    void login();
    void view_guide();

private:
    Ui::StartFBClass *ui;
    QJsonDocument list;
    QJsonParseError jsonError;
    void read_list();
    bool update_list();
    QSqlDatabase database;
};
