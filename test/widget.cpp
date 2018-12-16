#include "widget.h"
#include "ui_widget.h"
#include <unistd.h>
#include <stdio.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->btn_register,SIGNAL(clicked()),this,SLOT(slot_register()));
    //db = new QSqlDatabase;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");
    //db.setPort(3306);
    bool ok = db.open();
    if(!ok)
    {
        qDebug() << "err" << db.lastError().text();
    }
    qDebug() << "open";
    QSqlQuery query;
    QString sql = "create table if not exists userinfo(id int not null primary key,user varchar(20) not null,password varchar(20) not null);";
    ok = query.exec(sql);
    if(!ok)
        qDebug() << "err" << query.lastError().text();
}

Widget::~Widget()
{
    //db->close();
    delete ui;
    //delete db;
}

void Widget::slot_register()
{
    //qApp->quit();
    //this->close();
    qDebug() << "success!";
}
