#ifndef WUZIQI_H
#define WUZIQI_H

#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QVector>
#include <QLine>
#include <QMouseEvent>
#include <QList>
#include <QPushButton>
#include "user.h"

enum POINTER
{
    POINT_ALL,
    POINT_UP,
    POINT_DOWN,
    POINT_LEFT,
    POINT_RIGHT,
    POINT_LEFTUP,
    POINT_LEFTDOWN,
    POINT_RIGHTUP,
    POINT_RIGHTDOWN
};

class wuziqi : public QWidget
{
    Q_OBJECT
public:
    explicit wuziqi(QWidget *parent = 0);
    ~wuziqi();
    static wuziqi *instance();
    void setupUi();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    int fun(int x, int y, int user, POINTER pointer = POINT_ALL);
    void fun2(int x, int y, int user);
    int check(int a);
    void set_bit(int &a, int offset);
    void reset_bit(int &a,int offset);
    bool is_set_bit(int a,int offset);
signals:

public slots:
    void slot_start();
    void slot_back();
private:
    QPainter *painter;
    QGraphicsScene *scene;
    QGraphicsView *view;
    static wuziqi *p_thiz;
    QWidget *widget;
    QList<User *> *list;
    QPushButton *btn_start;
    QPushButton *btn_back;
    int buf[16][16];
    int buf_height[16][16];//权值
    int buf_height2[16][16];
};

#endif // WUZIQI_H
