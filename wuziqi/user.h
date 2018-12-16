#ifndef USER_H
#define USER_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>

class User : public QGraphicsItem
{
public:
    User(QColor color);
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *);
    QPainterPath shape();
    void setPoint(int x,int y);
    int getx() { return x; }
    int gety() { return y; }
private:
    QColor color;
    int x;
    int y;
};

#endif // USER_H
