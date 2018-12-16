            //б2
            if(is_set_bit(buf_2[i][j],0))
            {
                list_point2->clear();
                list_point3->clear();
                set_bit(buf_2[i][j],5);
                flag = 1;
                flag1 = 0;
                for(int k = 1;k < 5;k++)
                {
                    if(i + k > 15 || j - k < 0)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                    if(buf_2[i+k][j-k] == 0)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point2->append(point);
                    }
                    else if(is_set_bit(buf_2[i+k][j-k],0))
                    {
                        set_bit(buf_2[i+k][j-k],5);
                        flag++;
                    }
                    else
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                }
                if(!list_point3->isEmpty())
                {
                    x = list_point3->first()->x();
                    y = list_point3->first()->y();
                    int a = 5 - (x - j);
                    for(int k = 1;k <= a;k++)
                    {
                        if(k == a)
                        {
                            if(i - k < 0 || j + k > 15 || is_set_bit(buf_2[i-k][j+k],1))
                            {
                                QPoint *point = new QPoint(j+k,i-k);
                                list_point3->append(point);
                            }
                        }
                        if(i - k < 0 || j + k > 15)
                        {
                            list_point2->clear();
                            break;
                        }
                        if(is_set_bit(buf_2[i-k][j+k],1))
                        {
                            list_point2->clear();
                            break;
                        }
                    }
                }
                if(i - 1 < 0 || j + 1 > 15)
                {
                    QPoint *point = new QPoint(j+1,i-1);
                    list_point3->append(point);
                }
                if(!list_point2->isEmpty())
                {
                    x = 0;
                    y = 0;
                    if(list_point3->isEmpty())
                    {
                        flag1 = 0;
                    }
                    else
                    {
                        x = list_point3->first()->x();
                        y = list_point3->first()->y();
                    }
                    if(!list_point3->isEmpty() && list_point3->count() == 2)
                    {
                        flag1 = 1;
                    }
                    else if((y == -1 || x == 16) && is_set_bit(buf_2[y+1][x-1],0))
                    {
                        flag1 = 1;
                    }
                    else if((y != -1 && x != 16) && is_set_bit(buf_2[y-1][x+1],0))
                    {
                        flag1 = 1;
                    }
                    else
                    {
                        flag1 = 0;
                    }
                }
                if(flag == 1 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 5)
                        {
                            buf_3[y][x] = 5;
                        }
                        else if(buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                    }
                }
                else if(flag == 2 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                        else if(buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                    }
                }
                else if(flag == 3 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                        else if(buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                    }
                }
                else if(flag == 4 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                        else if(buf_3[y][x] < 100)
                        {
                            buf_3[y][x] = 100;
                        }
                    }
                }
                //qDebug() << __LINE__ << endl;
                list_point->append(*list_point2);
            }
            //б2
            if(is_set_bit(buf_2[i][j],0))
            {
                list_point2->clear();
                list_point3->clear();
                set_bit(buf_2[i][j],5);
                flag = 1;
                flag1 = 0;
                //qDebug() << __LINE__ << endl;
                for(int k = 1;k < 5;k++)
                {
                    if(i + k > 15 || j - k > 15)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                    if(buf_2[i+k][j-k] == 0)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point2->append(point);
                    }
                    else if(is_set_bit(buf_2[i+k][j-k],0))
                    {
                        set_bit(buf_2[i+k][j-k],5);
                        flag++;
                    }
                    else
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                }
                if(!list_point3->isEmpty())
                {
                    x = list_point3->first()->x();
                    y = list_point3->first()->y();
                    int a = 5 - (x - j);
                    for(int k = 1;k <= a;k++)
                    {
                        if(k == a)
                        {
                            if(i - k < 0 || j + k > 15 || is_set_bit(buf_2[i-k][j+k],1))
                            {
                                QPoint *point = new QPoint(j+k,i-k);
                                list_point3->append(point);
                            }
                        }
                        if(i - k < 0 || j + k > 15)
                        {
                            list_point2->clear();
                            break;
                        }
                        if(is_set_bit(buf_2[i-k][j+k],1))
                        {
                            list_point2->clear();
                            break;
                        }
                    }
                }
                if(i - 1 < 0 || j + 1 > 15)
                {
                    QPoint *point = new QPoint(j+1,i-1);
                    list_point3->append(point);
                }
                if(!list_point2->isEmpty())
                {
                    x = 0;
                    y = 0;
                    if(list_point3->isEmpty())
                    {
                        flag1 = 0;
                    }
                    else
                    {
                        x = list_point3->first()->x();
                        y = list_point3->first()->y();
                    }
                    if(!list_point3->isEmpty() && list_point3->count() == 2)
                    {
                        flag1 = 1;
                    }
                    else if((y == -1 || x == 16) && is_set_bit(buf_2[y+1][x-1],0))
                    {
                        flag1 = 1;
                    }
                    else if((y != -1 && x != 16) && is_set_bit(buf_2[y-1][x+1],0))
                    {
                        flag1 = 1;
                    }
                    else
                    {
                        flag1 = 0;
                    }
                }
                if(flag == 1 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 5)
                        {
                            buf_3[y][x] = 5;
                        }
                        else if(buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                    }
                }
                else if(flag == 2 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                        else if(buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                    }
                }
                else if(flag == 3 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                        else if(buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                    }
                }
                else if(flag == 4 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                        else if(buf_3[y][x] < 100)
                        {
                            buf_3[y][x] = 100;
                        }
                    }
                }
                //qDebug() << __LINE__ << endl;
                list_point->append(*list_point2);
            }
            //б2
            if(is_set_bit(buf_2[i][j],0))
            {
                list_point2->clear();
                list_point3->clear();
                set_bit(buf_2[i][j],5);
                flag = 1;
                flag1 = 0;
                //qDebug() << __LINE__ << endl;
                for(int k = 1;k < 5;k++)
                {
                    if(i + k > 15 || j - k > 15)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                    if(buf_2[i+k][j-k] == 0)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point2->append(point);
                    }
                    else if(is_set_bit(buf_2[i+k][j-k],0))
                    {
                        set_bit(buf_2[i+k][j-k],5);
                        flag++;
                    }
                    else
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                }
                if(!list_point3->isEmpty())
                {
                    x = list_point3->first()->x();
                    y = list_point3->first()->y();
                    int a = 5 - (x - j);
                    for(int k = 1;k <= a;k++)
                    {
                        if(k == a)
                        {
                            if(i - k < 0 || j + k > 15 || is_set_bit(buf_2[i-k][j+k],1))
                            {
                                QPoint *point = new QPoint(j+k,i-k);
                                list_point3->append(point);
                            }
                        }
                        if(i - k < 0 || j + k > 15)
                        {
                            list_point2->clear();
                            break;
                        }
                        if(is_set_bit(buf_2[i-k][j+k],1))
                        {
                            list_point2->clear();
                            break;
                        }
                    }
                }
                if(i - 1 < 0 || j + 1 > 15)
                {
                    QPoint *point = new QPoint(j+1,i-1);
                    list_point3->append(point);
                }
                if(!list_point2->isEmpty())
                {
                    x = 0;
                    y = 0;
                    if(list_point3->isEmpty())
                    {
                        flag1 = 0;
                    }
                    else
                    {
                        x = list_point3->first()->x();
                        y = list_point3->first()->y();
                    }
                    if(!list_point3->isEmpty() && list_point3->count() == 2)
                    {
                        flag1 = 1;
                    }
                    else if((y == -1 || x == 16) && is_set_bit(buf_2[y+1][x-1],0))
                    {
                        flag1 = 1;
                    }
                    else if((y != -1 && x != 16) && is_set_bit(buf_2[y-1][x+1],0))
                    {
                        flag1 = 1;
                    }
                    else
                    {
                        flag1 = 0;
                    }
                }
                if(flag == 1 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 5)
                        {
                            buf_3[y][x] = 5;
                        }
                        else if(buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                    }
                }
                else if(flag == 2 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                        else if(buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                    }
                }
                else if(flag == 3 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                        else if(buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                    }
                }
                else if(flag == 4 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                        else if(buf_3[y][x] < 100)
                        {
                            buf_3[y][x] = 100;
                        }
                    }
                }
                //qDebug() << __LINE__ << endl;
                list_point->append(*list_point2);
            }
            //б2
            if(is_set_bit(buf_2[i][j],0))
            {
                list_point2->clear();
                list_point3->clear();
                set_bit(buf_2[i][j],5);
                flag = 1;
                flag1 = 0;
                //qDebug() << __LINE__ << endl;
                for(int k = 1;k < 5;k++)
                {
                    if(i + k > 15 || j - k > 15)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                    if(buf_2[i+k][j-k] == 0)
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point2->append(point);
                    }
                    else if(is_set_bit(buf_2[i+k][j-k],0))
                    {
                        set_bit(buf_2[i+k][j-k],5);
                        flag++;
                    }
                    else
                    {
                        QPoint *point = new QPoint(j-k,i+k);
                        list_point3->append(point);
                        break;
                    }
                }
                if(!list_point3->isEmpty())
                {
                    x = list_point3->first()->x();
                    y = list_point3->first()->y();
                    int a = 5 - (x - j);
                    for(int k = 1;k <= a;k++)
                    {
                        if(k == a)
                        {
                            if(i - k < 0 || j + k > 15 || is_set_bit(buf_2[i-k][j+k],1))
                            {
                                QPoint *point = new QPoint(j+k,i-k);
                                list_point3->append(point);
                            }
                        }
                        if(i - k < 0 || j + k > 15)
                        {
                            list_point2->clear();
                            break;
                        }
                        if(is_set_bit(buf_2[i-k][j+k],1))
                        {
                            list_point2->clear();
                            break;
                        }
                    }
                }
                if(i - 1 < 0 || j + 1 > 15)
                {
                    QPoint *point = new QPoint(j+1,i-1);
                    list_point3->append(point);
                }
                if(!list_point2->isEmpty())
                {
                    x = 0;
                    y = 0;
                    if(list_point3->isEmpty())
                    {
                        flag1 = 0;
                    }
                    else
                    {
                        x = list_point3->first()->x();
                        y = list_point3->first()->y();
                    }
                    if(!list_point3->isEmpty() && list_point3->count() == 2)
                    {
                        flag1 = 1;
                    }
                    else if((y == -1 || x == 16) && is_set_bit(buf_2[y+1][x-1],0))
                    {
                        flag1 = 1;
                    }
                    else if((y != -1 && x != 16) && is_set_bit(buf_2[y-1][x+1],0))
                    {
                        flag1 = 1;
                    }
                    else
                    {
                        flag1 = 0;
                    }
                }
                if(flag == 1 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 5)
                        {
                            buf_3[y][x] = 5;
                        }
                        else if(buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                    }
                }
                else if(flag == 2 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 10)
                        {
                            buf_3[y][x] = 10;
                        }
                        else if(buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                    }
                }
                else if(flag == 3 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 20)
                        {
                            buf_3[y][x] = 20;
                        }
                        else if(buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                    }
                }
                else if(flag == 4 && !list_point2->isEmpty())
                {
                    for(int k = 0;k < list_point2->count();k++)
                    {
                        x = list_point2->at(k)->x();
                        y = list_point2->at(k)->y();
                        if(flag1 == 1 && buf_3[y][x] < 50)
                        {
                            buf_3[y][x] = 50;
                        }
                        else if(buf_3[y][x] < 100)
                        {
                            buf_3[y][x] = 100;
                        }
                    }
                }
                //qDebug() << __LINE__ << endl;
                list_point->append(*list_point2);
            }
