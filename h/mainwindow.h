#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCoreApplication>
#include <QMessageBox>
#include <QString>
#include <QDateTime>
#include <QProcess>
#include <QVector>
#include <QDebug>

#include "applicationitems.h"
#include "showallintable.h"

// Database
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<ListItems*> listOfItems;
    QString DatabaseAddress = QCoreApplication::applicationDirPath()+"/MainInfo.db";
    QSqlDatabase mydb;
    QTimer *appTime;
    QString GetDayName();
    QString ConvertToNativeDayName(QString Input);
    bool onlyOnce = false;
    void prepareDatabase();
    void ReadFromDatabase();

private slots:
    void mainTimer();
    void on_autoshutdownbtn_triggered(bool checked);
    void on_AboutBtn_triggered();
    void on_SaveBtn_clicked();
    void on_AddAFile_clicked();
    void on_adding_data(const ListItems &listofitems);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
