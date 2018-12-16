#include "user.h"

User::User(QColor color)
{
    this->color = color;
}

QRectF User::boundingRect() const
{
    return QRectF(x,y,26,26);
}

void User::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(),QBrush(color));

    painter->restore();
}

QPainterPath User::shape()
{
    QPainterPath p;
    p.addEllipse(x,y,26,26);
    return p;
}

void User::setPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}

