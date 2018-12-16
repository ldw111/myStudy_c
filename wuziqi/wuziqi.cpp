#include "wuziqi.h"
#include "assert.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <ctime>
#include <cstdlib>

wuziqi *wuziqi::p_thiz = NULL;

wuziqi::wuziqi(QWidget *parent) : QWidget(parent)
{
    wuziqi::p_thiz = this;
    //user1 = new User(Qt::white);
    //user2 = new User(Qt::black);

    list = new QList<User *>;
    list->clear();
    list->append(NULL);
//    painter = new QPainter(this);
//    this->setupUi();
    this->setFixedSize(600,510);
    this->setWindowTitle(tr("五子棋"));
    //qDebug() << "hello" << endl;
    btn_start = new QPushButton(tr("开始"),this);
    btn_back = new QPushButton(tr("撤回"),this);
    widget = new QWidget(this);
    widget->setGeometry(30,30,450,450);
    scene = new QGraphicsScene(widget);
    scene->addRect(0,0,450,450);
    view = new QGraphicsView(scene,widget);
    scene->setSceneRect(0,0,450,450);
    QPixmap p(30,30);
    QPainter paint(&p);
    paint.setBrush(QBrush(Qt::gray));
    paint.drawRect(0,0,30,30);
    view->setBackgroundBrush(QBrush(p));

    btn_start->move(500,400);
    btn_back->move(500,440);

    memset(buf,0,sizeof(buf));
    memset(buf_height,0,sizeof(buf_height));
    memset(buf_height2,0,sizeof(buf_height2));
    connect(btn_start,SIGNAL(clicked(bool)),this,SLOT(slot_start()));
    connect(btn_back,SIGNAL(clicked(bool)),this,SLOT(slot_back()));
}

wuziqi::~wuziqi()
{
    //delete painter;
    for(int i = 0;!list->isEmpty();i++)
    {
        delete list->at(0);
        list->removeAt(0);
    }
    delete list;
    delete widget;
}

wuziqi *wuziqi::instance()
{
    return wuziqi::p_thiz;
}

void wuziqi::setupUi()
{
    QVector<QLine> vec;
    vec.clear();
    painter = new QPainter(this);
    painter->setPen(Qt::black);
    painter->drawRect(10,10,450,450);
    //painter->drawLine(10,40,460,40);
    for(int i = 0;i < 15;i++)
    {
        QLine line(10,40+30*i,460,40+30*i);
        vec << line;
    }
    for(int i = 0;i < 15;i++)
    {
        QLine line(40+30*i,10,40+30*i,460);
        vec << line;
    }
    painter->drawLines(vec);
}

void wuziqi::paintEvent(QPaintEvent *)
{
    //this->setupUi();
}

void wuziqi::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug() << __LINE__;
        int x = event->x();
        int y = event->y();
        if(x % 30 > 15)
            x = x / 30 * 30 - 13;
        else
            x = x / 30 * 30 - 43;
        if(y % 30 > 15)
            y = y / 30 * 30 - 13;
        else
            y = y / 30 * 30 - 43;
        qDebug() << "(" << (x+13)/30 << "," << (y+13)/30 << ")" << endl;
        if(x < -13 || x > 467 || y < -13 || y > 467)
            return;
        if(!buf[(y+13)/30][(x+13)/30])
        {
            if(list->count()%2)
            {
                User *user1;
                user1 = new User(Qt::black);
                list->append(user1);
                user1->setPoint(x,y);
                scene->addItem(user1);
                buf[(y+13)/30][(x+13)/30] = 1;
            }
            else
            {
                User *user2 = new User(Qt::white);
                list->append(user2);
                user2->setPoint(x,y);
                scene->addItem(user2);
                buf[(y+13)/30][(x+13)/30] = 2;
            }
            int result = check(5);
            if(result == 1)
            {
                QMessageBox::information(this,"successful","you win!",QMessageBox::Ok);
                widget->installEventFilter(this);
                return;
            }
            else if(result == 2)
            {
                QMessageBox::information(this,"fail","you fail!",QMessageBox::Ok);
                widget->installEventFilter(this);
                return;
            }
            //memcpy(oldbuf_height,buf_height,sizeof(buf_height));
            //qDebug() << __LINE__;
            srand(time(NULL));
            QList<QPoint *> *list_point = new QList<QPoint *>;
            list_point->clear();
            int max = fun((x+13)/30,(y+13)/30,1);
            fun2((x+13)/30,(y+13)/30,1);
            int max2 = 0;
            for(int i = 0;i < 16;i++)
            {
                for(int j = 0;j < 16;j++)
                {
                    if(max2 < buf_height2[i][j])
                        max2 = buf_height2[i][j];
                }
            }
            int m,n;
            for(int i = 0;i < 16;i++)
            {
                for(int j = 0;j < 16;j++)
                {
                    if(max >= 10 && max2 >= max)
                    {
                        if(max2 == buf_height2[i][j])
                        {
                            int black_max = buf_height[i][j];
                            if(buf_height[i][j] >= black_max)
                            {
                                black_max = buf_height[i][j];
                                QPoint *point = new QPoint(j,i);
                                list_point->append(point);
                            }
                        }
                    }
                    else
                    {
                        if(max == buf_height[i][j])
                        {
                            int white_max = 0;
                            if(buf_height2[i][j] >= white_max)
                            {
                                white_max = buf_height2[i][j];
                                QPoint *point = new QPoint(j,i);
                                list_point->append(point);
                            }
                        }
                    }
                }
            }
            int index = rand()%list_point->count();
            m = list_point->at(index)->x();
            n = list_point->at(index)->y();
            //qDebug() << __LINE__;
            User *user2 = new User(Qt::white);
            list->append(user2);
            user2->setPoint(m*30-13,n*30-13);
            scene->addItem(user2);
            buf[n][m] = 2;
            //buf_height[i][j] = -1;
            //qDebug("(%d,%d),%d",m,n,__LINE__);
            fun(m,n,2);
            fun2(m,n,2);
            result = check(5);
            if(result == 2)
            {
                QMessageBox::information(this,"fail","you fail!",QMessageBox::Ok);
                widget->installEventFilter(this);
                return;
            }
            //qDebug() << __LINE__;
        }
//        scene->addEllipse(x,y,26,26,QPen(Qt::black),QBrush(Qt::black));
//        view->setScene(scene);
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

bool wuziqi::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == widget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
                return true;
        }
        return false;
    }
    else
    {
        return QWidget::eventFilter(obj,event);
    }
}

int wuziqi::fun(int x, int y, int user, POINTER pointer)
{
    int count = 0;
    bool flag = false;
    int a,b;
    //buf_height[y][x] = -1;
    //buf_height2[y][x] = -1;
    if(user == 1)
    {
        a = 1;
        b = 2;
    }
    else if(user == 2)
    {
        a = 2;
        b = 1;
    }
    else
    {
        assert(0);
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_RIGHT)) && (x+1 < 16))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if(x - i < 0)
                break;
            if(buf[y][x-i] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if(x + i > 15)
                break;
            if(buf[y][x+i] == b)
                break;
            cnt++;
        }
        if(buf[y][x+1] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if(x-i < 0)
                {
                    flag = true;
                    break;
                }
                if(buf[y][x-i] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y][x-i] == a)
                {
                    count++;
                }
                else if(buf[y][x-i] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if(x+i > 15)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y][x+i] == 0)
                {
                    break;
                }
                if(buf[y][x+i] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y][x+i] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y][x+1] < (5*count - 5)))
            {
                buf_height[y][x+1] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y][x+1] < 5*count)
            {
                buf_height[y][x+1] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y][x+1] < (5*count - 5)))
            {
                buf_height2[y][x+1] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y][x+1] < 5*count)
            {
                buf_height2[y][x+1] = 5*count;
            }
        }
        else if(buf[y][x+1] == a)
        {
            fun(x+1,y,a,POINT_RIGHT);
        }
        else if(buf[y][x+1] == b)
        {

        }
        else
        {
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_LEFT)) && (x-1 > 0))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if(x - i < 0)
                break;
            if(buf[y][x-i] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if(x + i > 15)
                break;
            if(buf[y][x+i] == b)
                break;
            cnt++;
        }
        if(buf[y][x-1] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if(x+i > 15)
                {
                    flag = true;
                    break;
                }
                if(buf[y][x+i] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y][x+i] == a)
                {
                    count++;
                }
                else if(buf[y][x+i] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if(x-i < 0)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y][x-i] == 0)
                {
                    break;
                }
                if(buf[y][x-i] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y][x-i] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y][x-1] < (5*count - 5)))
            {
                buf_height[y][x-1] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y][x-1] < 5*count)
            {
                buf_height[y][x-1] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y][x-1] < (5*count - 5)))
            {
                buf_height2[y][x-1] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y][x-1] < 5*count)
            {
                buf_height2[y][x-1] = 5*count;
            }
        }
        else if(buf[y][x-1] == a)
        {
            fun(x-1,y,a,POINT_LEFT);
        }
        else if(buf[y][x-1] == b)
        {

        }
        else
        {
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_DOWN)) && (y+1 < 16))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if(y - i < 0)
                break;
            if(buf[y-i][x] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if(y + i > 15)
                break;
            if(buf[y+i][x] == b)
                break;
            cnt++;
        }
        if(buf[y+1][x] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if(y-i < 0)
                {
                    flag = true;
                    break;
                }
                if(buf[y-i][x] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y-i][x] == a)
                {
                    count++;
                }
                else if(buf[y-i][x] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if(y+i > 15)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y+i][x] == 0)
                {
                    break;
                }
                if(buf[y+i][x] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y+i][x] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y+1][x] < (5*count - 5)))
            {
                buf_height[y+1][x] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y+1][x] < 5*count)
            {
                buf_height[y+1][x] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y+1][x] < (5*count - 5)))
            {
                buf_height2[y+1][x] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y+1][x] < 5*count)
            {
                buf_height2[y+1][x] = 5*count;
            }
        }
        else if(buf[y+1][x] == a)
        {
            fun(x,y+1,a,POINT_DOWN);
        }
        else if(buf[y+1][x] == b)
        {

        }
        else
        {
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_UP)) && (y-1 > 0))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if(y - i < 0)
                break;
            if(buf[y-i][x] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if(y + i > 15)
                break;
            if(buf[y+i][x] == b)
                break;
            cnt++;
        }
        if(buf[y-1][x] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if(y+i > 15)
                {
                    flag = true;
                    break;
                }
                if(buf[y+i][x] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y+i][x] == a)
                {
                    count++;
                }
                else if(buf[y+i][x] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if(y-i < 0)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y-i][x] == 0)
                {
                    break;
                }
                if(buf[y-i][x] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y-i][x] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y-1][x] < (5*count - 5)))
            {
                buf_height[y-1][x] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y-1][x] < 5*count)
            {
                buf_height[y-1][x] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y-1][x] < (5*count - 5)))
            {
                buf_height2[y-1][x] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y-1][x] < 5*count)
            {
                buf_height2[y-1][x] = 5*count;
            }
        }
        else if(buf[y-1][x] == a)
        {
            fun(x,y-1,a,POINT_UP);
        }
        else if(buf[y-1][x] == b)
        {

        }
        else
        {
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_LEFTUP)) && ((y-1 > 0) && (x-1 > 0)))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if((y - i < 0) || (x - i < 0))
                break;
            if(buf[y-i][x-i] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if((y + i > 15) || (x + i > 15))
                break;
            if(buf[y+i][x+i] == b)
                break;
            cnt++;
        }
        if(buf[y-1][x-1] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if((y+i > 15) || (x+i > 15))
                {
                    flag = true;
                    break;
                }
                if(buf[y+i][x+i] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y+i][x+i] == a)
                {
                    count++;
                }
                else if(buf[y+i][x+i] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if((x-i < 0) || (y-i < 0))
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y-i][x-i] == 0)
                {
                    break;
                }
                if(buf[y-i][x-i] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y-i][x-i] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y-1][x-1] < (5*count - 5)))
            {
                buf_height[y-1][x-1] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y-1][x-1] < 5*count)
            {
                buf_height[y-1][x-1] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y-1][x-1] < (5*count - 5)))
            {
                buf_height2[y-1][x-1] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y-1][x-1] < 5*count)
            {
                buf_height2[y-1][x-1] = 5*count;
            }
        }
        else if(buf[y-1][x-1] == a)
        {
            fun(x-1,y-1,a,POINT_LEFTUP);
        }
        else if(buf[y-1][x-1] == b)
        {

        }
        else
        {
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_LEFTDOWN)) && ((y+1 < 16) && (x-1 > 0)))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if((y + i > 15) || (x - i < 0))
                break;
            if(buf[y+i][x-i] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if((y - i < 0) || (x + i > 15))
                break;
            if(buf[y-i][x+i] == b)
                break;
            cnt++;
        }
        if(buf[y+1][x-1] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if((y-i < 0) || (x+i > 15))
                {
                    flag = true;
                    break;
                }
                if(buf[y-i][x+i] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y-i][x+i] == a)
                {
                    count++;
                }
                else if(buf[y-i][x+i] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if((x-i < 0) || (y+i > 15))
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y+i][x-i] == 0)
                {
                    break;
                }
                if(buf[y+i][x-i] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y+i][x-i] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y+1][x-1] < (5*count - 5)))
            {
                buf_height[y+1][x-1] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y+1][x-1] < 5*count)
            {
                buf_height[y+1][x-1] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y+1][x-1] < (5*count - 5)))
            {
                buf_height2[y+1][x-1] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y+1][x-1] < 5*count)
            {
                buf_height2[y+1][x-1] = 5*count;
            }
        }
        else if(buf[y+1][x-1] == a)
        {
            fun(x-1,y+1,a,POINT_LEFTDOWN);
        }
        else if(buf[y+1][x-1] == b)
        {

        }
        else
        {
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_RIGHTUP)) && ((y-1 > 0) && (x+1 < 16)))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if((y - i < 0) || (x + i > 15))
                break;
            if(buf[y-i][x+i] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if((y + i > 15) || (x - i < 0))
                break;
            if(buf[y+i][x-i] == b)
                break;
            cnt++;
        }
        if(buf[y-1][x+1] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if((y+i > 15) || (x-i < 0))
                {
                    flag = true;
                    break;
                }
                if(buf[y+i][x-i] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y+i][x-i] == a)
                {
                    count++;
                }
                else if(buf[y+i][x-i] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if((x+i > 15) || (y-i < 0))
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y-i][x+i] == 0)
                {
                    break;
                }
                if(buf[y-i][x+i] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y-i][x+i] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y-1][x+1] < (5*count - 5)))
            {
                buf_height[y-1][x+1] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y-1][x+1] < 5*count)
            {
                buf_height[y-1][x+1] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y-1][x+1] < (5*count - 5)))
            {
                buf_height2[y-1][x+1] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y-1][x+1] < 5*count)
            {
                buf_height2[y-1][x+1] = 5*count;
            }
        }
        else if(buf[y-1][x+1] == a)
        {
            fun(x-1,y-1,a,POINT_RIGHTUP);
        }
        else if(buf[y-1][x+1] == b)
        {

        }
        else
        {qDebug() << buf[y-1][x+1];
            assert(0);
        }
    }
    if(((pointer == POINT_ALL) || (pointer == POINT_RIGHTDOWN)) && ((y+1 < 16) && (x+1 < 16)))
    {
        int cnt = 0;
        count = 0;
        flag = false;
        for(int i = 1;i < 5;i++)
        {
            if((y + i > 15) || (x + i > 15))
                break;
            if(buf[y+i][x+i] == b)
                break;
            cnt++;
        }
        for(int i = 1;i < 5;i++)
        {
            if((y - i < 0) || (x - i < 0))
                break;
            if(buf[y-i][x-i] == b)
                break;
            cnt++;
        }
        if(buf[y+1][x+1] == 0)
        {
            for(int i = 0;i < 5;i++)
            {
                if((y-i < 0) || (x-i < 0))
                {
                    flag = true;
                    break;
                }
                if(buf[y-i][x-i] == b)
                {
                    flag = true;
                    break;
                }
                if(buf[y-i][x-i] == a)
                {
                    count++;
                }
                else if(buf[y-i][x-i] == 0)
                {
                    break;
                }
                else
                {
                    assert(0);
                }
            }
            for(int i = 2;i < 5;i++)
            {
                bool flag1 = false;
                if((x+i > 15) || (y+i > 15))
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y+i][x+i] == 0)
                {
                    break;
                }
                if(buf[y+i][x+i] == b)
                {
                    if(flag1)
                        flag = true;
                    break;
                }
                if(buf[y+i][x+i] == a)
                {
                    flag1 = true;
                    count++;
                }
            }
            if(count == 4)
                count++;
            if(cnt < 4)
            {

            }
            else if((user == 1) && flag && (buf_height[y+1][x+1] < (5*count - 5)))
            {
                buf_height[y+1][x+1] = 5*count - 5;
            }
            else if((user == 1) && buf_height[y+1][x+1] < 5*count)
            {
                buf_height[y+1][x+1] = 5*count;
            }
            else if((user == 2) && flag && (buf_height2[y+1][x+1] < (5*count - 5)))
            {
                buf_height2[y+1][x+1] = 5*count - 5;
            }
            else if((user == 2) && buf_height2[y+1][x+1] < 5*count)
            {
                buf_height2[y+1][x+1] = 5*count;
            }
        }
        else if(buf[y+1][x+1] == a)
        {
            fun(x+1,y+1,a,POINT_RIGHTDOWN);
        }
        else if(buf[y+1][x+1] == b)
        {

        }
        else
        {
            assert(0);
        }
    }

    int max = 0;
    for(int i = 0;i < 16;i++)
    {
        for(int j = 0;j < 16;j++)
        {
            if((user == 1) && (max < buf_height[i][j]))
                max = buf_height[i][j];
            else if((user == 2) && (max < buf_height2[i][j]))
                max = buf_height2[i][j];
        }
    }
    return max;
}

void wuziqi::fun2(int x, int y,int user)
{
    buf_height2[y][x] = -1;
    buf_height[y][x] = -1;
    int a,b;
    if(user == 1)
    {
        a = 1;
        b = 2;
    }
    else if(user == 2)
    {
        a = 2;
        b = 1;
    }
    else
    {
        assert(0);
    }
    int count = 0;
    //qDebug() << __LINE__;
    //右
    for(int i = 1;i < 5;i++)
    {
        if(x+i > 15)
            break;
        if(buf[y][x+i] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y][x+i] == max))
                buf_height[y][x+i] = max - 5;
            else if((user == 1) && (buf_height2[y][x+i] == max))
                    buf_height2[y][x+i] = max - 5;
        }
        if(buf[y][x+i] == a)
        {
            break;
        }
        if(buf[y][x+i] == b)
        {
            count++;
        }
    }
    //左
    count = 0;
    //qDebug() << __LINE__;
    for(int i = 1;i < 5;i++)
    {
        if(x-i < 0)
            break;
        if(buf[y][x-i] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y][x-i] == max))
                buf_height[y][x-i] = max - 5;
            else if((user == 1) && (buf_height2[y][x-i] == max))
                    buf_height2[y][x-i] = max - 5;
        }
        if(buf[y][x-i] == a)
        {
            break;
        }
        if(buf[y][x-i] == b)
        {
            count++;
        }
    }
    //下
    count = 0;
    //qDebug() << __LINE__;
    for(int i = 1;i < 5;i++)
    {
        if(y+i > 15)
            break;
        if(buf[y+i][x] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y+i][x] == max))
                buf_height[y+i][x] = max - 5;
            else if((user == 1) && (buf_height2[y+i][x] == max))
                    buf_height2[y+i][x] = max - 5;
        }
        if(buf[y+i][x] == a)
        {
            break;
        }
        if(buf[y+i][x] == b)
        {
            count++;
        }
    }
    //上
    count = 0;
    //qDebug() << __LINE__;
    for(int i = 1;i < 5;i++)
    {
        if(y-i < 0)
            break;
        if(buf[y-i][x] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y-i][x] == max))
                buf_height[y-i][x] = max - 5;
            else if((user == 1) && (buf_height2[y-i][x] == max))
                    buf_height2[y-i][x] = max - 5;
        }
        if(buf[y-i][x] == a)
        {
            break;
        }
        if(buf[y-i][x] == b)
        {
            count++;
        }
    }
    //右上
    count = 0;
    //qDebug() << __LINE__;
    for(int i = 1;i < 5;i++)
    {
        if((x+i > 15) || (y-i < 0))
            break;
        if(buf[y-i][x+i] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y-i][x+i] == max))
                buf_height[y-i][x+i] = max - 5;
            else if((user == 1) && (buf_height2[y-i][x+i] == max))
                    buf_height2[y-i][x+i] = max - 5;
        }
        if(buf[y-i][x+i] == a)
        {
            break;
        }
        if(buf[y-i][x+i] == b)
        {
            count++;
        }
    }
    //左上
    count = 0;
    for(int i = 1;i < 5;i++)
    {
        if((x-i < 0) || (y-i < 0))
            break;
        if(buf[y-i][x-i] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y-i][x-i] == max))
                buf_height[y-i][x-i] = max - 5;
            else if((user == 1) && (buf_height2[y-i][x-i] == max))
                    buf_height2[y-i][x-i] = max - 5;
        }
        if(buf[y-i][x-i] == a)
        {
            break;
        }
        if(buf[y-i][x-i] == b)
        {
            count++;
        }
    }
    //右下
    count = 0;
    for(int i = 1;i < 5;i++)
    {
        if((y+i > 15) ||(x+i > 15))
            break;
        if(buf[y+i][x+i] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y+i][x+i] == max))
                buf_height[y+i][x+i] = max - 5;
            else if((user == 1) && (buf_height2[y+i][x+i] == max))
                    buf_height2[y+i][x+i] = max - 5;
        }
        if(buf[y+i][x+i] == a)
        {
            break;
        }
        if(buf[y+i][x+i] == b)
        {
            count++;
        }
    }
    //左下
    count = 0;
    for(int i = 1;i < 5;i++)
    {
        if((y+i > 15) || (x-i < 0))
            break;
        if(buf[y+i][x-i] == 0)
        {
            if(count == 0)
                break;
            int max = 5*count;
            if((user == 2) && (buf_height[y+i][x-i] == max))
                buf_height[y+i][x-i] = max - 5;
            else if((user == 1) && (buf_height2[y+i][x-i] == max))
                    buf_height2[y+i][x-i] = max - 5;
        }
        if(buf[y+i][x-i] == a)
        {
            break;
        }
        if(buf[y+i][x-i] == b)
        {
            count++;
        }
    }
}

int wuziqi::check(int a)
{
    int x =(list->last()->getx()+13)/30;
    int y =(list->last()->gety()+13)/30;
    int count = 1;
    switch (buf[y][x])
    {
    case 0:
        break;
    case 1:
        for(int i = 1;(i < a) && (y-i >= 0);i++)
        {
            if(buf[y-i][x] == 1)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (y+i <= 15);i++)
        {
            if(buf[y+i][x] == 1)
                count++;
            else
                break;
        }
        if(count >= a)
            return 1;
        count = 1;
        for(int i = 1;(i < a) && (x-i >= 0);i++)
        {
            if(buf[y][x-i] == 1)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (x+i <= 15);i++)
        {
            if(buf[y][x+i] == 1)
                count++;
            else
                break;
        }
        if(count >= a)
            return 1;
        count = 1;
        for(int i = 1;(i < a) && (y-i >= 0) && (x-i) >= 0;i++)
        {
            if(buf[y-i][x-i] == 1)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (y+i <= 15) && (x+i) <= 15;i++)
        {
            if(buf[y+i][x+i] == 1)
                count++;
            else
                break;
        }
        if(count >= a)
            return 1;
        count = 1;
        for(int i = 1;(i < a) && (y-i >= 0) && (x+i) <= 15;i++)
        {
            if(buf[y-i][x+i] == 1)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (y+i <= 15) && (x-i) >= 0;i++)
        {
            if(buf[y+i][x-i] == 1)
                count++;
            else
                break;
        }
        if(count >= a)
            return 1;
        break;
    case 2:
        for(int i = 1;(i < a) && (y-i >= 0);i++)
        {
            if(buf[y-i][x] == 2)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (y+i <= 15);i++)
        {
            if(buf[y+i][x] == 2)
                count++;
            else
                break;
        }
        if(count >= a)
            return 2;
        count = 1;
        for(int i = 1;(i < a) && (x-i >= 0);i++)
        {
            if(buf[y][x-i] == 2)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (x+i <= 15);i++)
        {
            if(buf[y][x+i] == 2)
                count++;
            else
                break;
        }
        if(count >= a)
            return 2;
        count = 1;
        for(int i = 1;(i < a) && (y-i >= 0) && (x-i) >= 0;i++)
        {
            if(buf[y-i][x-i] == 2)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (y+i <= 15) && (x+i) <= 15;i++)
        {
            if(buf[y+i][x+i] == 2)
                count++;
            else
                break;
        }
        if(count >= a)
            return 2;
        count = 1;
        for(int i = 1;(i < a) && (y-i >= 0) && (x+i) <= 15;i++)
        {
            if(buf[y-i][x+i] == 2)
                count++;
            else
                break;
        }
        for(int i = 1;(i < a) && (y+i <= 15) && (x-i) >= 0;i++)
        {
            if(buf[y+i][x-i] == 2)
                count++;
            else
                break;
        }
        if(count >= a)
            return 2;
        break;
    default:
        //exit(1);
        break;
    }
    return 0;
}

void wuziqi::set_bit(int &a,int offset)
{
    int b = 1 << offset;
    a |= b;
}

void wuziqi::reset_bit(int &a, int offset)
{
    int b = ~(1 << offset);
    a &= b;
}

bool wuziqi::is_set_bit(int a, int offset)
{
    int b = 1 << offset;
    int c = a | b;
    return !(a^c);
}

void wuziqi::slot_start()
{
    widget->removeEventFilter(this);
    for(int i = 0;!list->isEmpty();i++)
    {
        delete list->at(0);
        list->removeAt(0);
    }
    list->append(NULL);
    memset(buf,0,sizeof(buf));
    memset(buf_height,0,sizeof(buf_height));
    memset(buf_height2,0,sizeof(buf_height2));
}

void wuziqi::slot_back()
{
    if(list->last() == NULL)
        return;
    buf[(list->last()->gety()+13)/30][(list->last()->getx()+13)/30] = 0;
    delete list->last();
    list->removeLast();
    buf[(list->last()->gety()+13)/30][(list->last()->getx()+13)/30] = 0;
    delete list->last();
    list->removeLast();
    //fun((list->last()->getx()+13)/30,(list->last()->gety()+13)/30);
    if(list->last() != NULL)
        check(5);
}
