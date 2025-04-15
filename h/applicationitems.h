#ifndef APPLICATIONITEMS_H
#define APPLICATIONITEMS_H

#include <QString>
#include <QTime>
#include <QVector>

struct ListItems
{
    int Id;
    QString DayName;
    QTime Time;
    QTime EndTime;
    QString FileAddress;
};

#endif // APPLICATIONITEMS_H
