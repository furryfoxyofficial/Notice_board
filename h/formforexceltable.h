#ifndef FORMFOREXCELTABLE_H
#define FORMFOREXCELTABLE_H

#include <QDateTime>
#include <QWidget>

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "mainwindow.h"

namespace Ui {
class FormForExcelTable;
}

class FormForExcelTable : public QWidget
{
    Q_OBJECT

public:
    explicit FormForExcelTable(QWidget *parent = nullptr);
    ~FormForExcelTable();
    void setListData(int id, QString day, QTime time, QTime endtime, QString FileAddress);
    void editFileRecords(int id);
    void deleteFileRecords(int id);

private slots:
    void on_DeleteBtn_clicked();

private:
    Ui::FormForExcelTable *ui;
};

#endif // FORMFOREXCELTABLE_H
