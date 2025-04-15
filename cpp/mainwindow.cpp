#include "mainwindow.h"
#include "formforexceltable.h"
#include "ui_mainwindow.h"
#include "presentationday.h"
#include "aboutme.h"
#include <QLocale>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , appTime(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(appTime,&QTimer::timeout,this,&MainWindow::mainTimer);
    appTime->start(1000);
    ReadFromDatabase();
    showMinimized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::GetDayName()
{
    QDateTime curnttime = QDateTime::currentDateTime();
    QLocale locale(QLocale::English);
    QString dayOfWeek = locale.toString(curnttime,"dddd");
    return dayOfWeek;
}

QString MainWindow::ConvertToNativeDayName(QString Input)
{
    std::map<QString,QString> dayMap
        {
            {"Monday", "دوشنبه"},
            {"Tuesday", "سهشنبه"},
            {"Wednesday", "چهارشنبه"},
            {"Thursday", "پنجشنبه"},
            {"Friday", "جمعه"},
            {"Saturday", "شنبه"},
            {"Sunday", "یکشنبه"}
        };
    auto it = dayMap.find(Input);
    if (it != dayMap.end())
    {
        return it->second;
    }
    else
    {
        return "Unknown";
    }
}

void MainWindow::prepareDatabase()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(DatabaseAddress);
    if (!mydb.open())
    {
        QMessageBox::critical(this,"خطا","عدم بازکردن دیتابیس");
        return;
    }
    mydb.exec("CREATE TABLE IF NOT EXISTS infotable (id NUMERIC (4),dayname TEXT (10),time TEXT (8), endtime TEXT (8), fileaddress TEXT (5000));");
}

void MainWindow::mainTimer()
{
    QTime now = QTime::currentTime();
    for (const auto& data : listOfItems)
    {
        if (ConvertToNativeDayName(GetDayName()) == data->DayName)
        {
            if (now.hour() == data->Time.hour() && now.minute() == data->Time.minute() && now.second() == data->Time.second())
            {
                ShowAllInTable *show = new ShowAllInTable(this);
                show->runExcel(data->FileAddress);
                show->startAutoScroll();
                show->showMaximized();
            }
        }
    }
}

void MainWindow::ReadFromDatabase()
{
    prepareDatabase();
    QSqlQuery db(mydb);
    db.exec("SELECT id, dayname, time, endtime, fileaddress FROM infotable");
    while (db.next())
    {
        ListItems *items = new ListItems;
        items->Id = db.value(0).toInt();
        items->DayName = db.value(1).toString();
        items->Time = db.value(2).toTime();
        items->EndTime = db.value(3).toTime();
        items->FileAddress = db.value(4).toString();
        listOfItems.push_back(items);
        FormForExcelTable *form = new FormForExcelTable(this);
        form->setListData(items->Id,items->DayName,items->Time,items->EndTime,items->FileAddress);
        ui->VerticalSpaceBox->addWidget(form);
    }
    if (!db.exec())
    {
        QMessageBox::critical(this,"خطا",db.lastError().text());
    }
}

void MainWindow::on_AboutBtn_triggered()
{
    AboutMe *aboutme = new AboutMe(this);
    aboutme->show();
}

void MainWindow::on_autoshutdownbtn_triggered(bool checked)
{
    if (checked == true)
    {
        QTime targetTime(19,40);
        QTime currentTime = QTime::currentTime();
        int secodesRemaning = currentTime.secsTo(targetTime);
        qDebug() << QProcess::startDetached("shutdown",QStringList() << "-s" << "-t" << QString::number(secodesRemaning));
        QMessageBox::about(this,"اطلاعات","خاموشی خودکار رایانه فعال شد");
    }
    else
    {
        QMessageBox::about(this,"اطلاعات","خاموشی خودکار رایانه غیر فعال شد");
        qDebug() << QProcess::startDetached("shutdown",QStringList() << "-a");
    }
}

void MainWindow::on_SaveBtn_clicked()
{
    QSqlQuery dbquery(mydb);
    dbquery.exec("DELETE FROM infotable");
    for (const ListItems *item : listOfItems)
    {
        dbquery.prepare("INSERT INTO infotable (id,dayname,time,endtime,fileaddress) \
        VALUES (:ID,:DAYNAME,:TIME,:ENDTIME,:FILEADDRESS)");
        dbquery.bindValue(":ID", item->Id);
        dbquery.bindValue(":DAYNAME", item->DayName);
        dbquery.bindValue(":TIME", item->Time);
        dbquery.bindValue(":ENDTIME", item->EndTime);
        dbquery.bindValue(":FILEADDRESS", item->FileAddress);
        if (!dbquery.exec())
        {
            QMessageBox::critical(this, "خطا", "نمیتوان مقادیر را در دیتابیس ذخیره کرد زیرا: " +
            dbquery.lastError().text() + dbquery.lastQuery());
        }
    }
}

void MainWindow::on_AddAFile_clicked()
{
    // for (const auto& data : listOfItems)
    // {
    //     ShowAllInTable *show = new ShowAllInTable(this);
    //     show->runExcel(data->FileAddress);
    //     show->startAutoScroll();
    //     show->showMaximized();
    // }
    PresentationDay *present = new PresentationDay(this);
    connect(present,&PresentationDay::AddData,this,&MainWindow::on_adding_data);
    present->show();
}

void MainWindow::on_adding_data(const ListItems &listofitems)
{
    listOfItems.append(new ListItems(listofitems));
    FormForExcelTable *form = new FormForExcelTable(this);
    form->setListData(listofitems.Id,listofitems.DayName,listofitems.Time,listofitems.EndTime,listofitems.FileAddress);
    ui->VerticalSpaceBox->addWidget(form);
}
