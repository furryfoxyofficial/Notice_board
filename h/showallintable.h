#ifndef SHOWALLINTABLE_H
#define SHOWALLINTABLE_H

#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QScrollBar>
#include <QTimer>
#include <QScreen>
#include <QPropertyAnimation>

#include <xlsxdocument.h>
#include <xlsxcell.h>

namespace Ui {
class ShowAllInTable;
}

class ShowAllInTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowAllInTable(QWidget *parent = nullptr);
    ~ShowAllInTable();
    void runExcel(QString &fileformat);
    void startAutoScroll();
    QPropertyAnimation *Animation;
    QPixmap pix;


private slots:
    void autoScroll();
    void resizeColumn(int column);
    void resizeRow(int row);
    void restartAnimation();

private:
    Ui::ShowAllInTable *ui;
    QTimer *timer;
};

#endif // SHOWALLINTABLE_H
