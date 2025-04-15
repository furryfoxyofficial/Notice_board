#include "formforexceltable.h"
#include "ui_formforexceltable.h"

FormForExcelTable::FormForExcelTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormForExcelTable)
{
    ui->setupUi(this);
}

FormForExcelTable::~FormForExcelTable()
{
    delete ui;
}

void FormForExcelTable::setListData(int id, QString day, QTime time, QTime endtime, QString FileAddress)
{
    ui->IdLbl->setText(QString("%1").arg(id));
    ui->DayLbl->setText(QString("%1").arg(day));
    ui->TimeLbl->setText(QString("%1").arg(time.toString()));
    ui->EndTimeLbl->setText(QString("%1").arg(endtime.toString()));
    ui->FileNameLbl->setText(QString("%1").arg(FileAddress));
}


void FormForExcelTable::on_DeleteBtn_clicked()
{
    QMessageBox::information(this,"info","این گزینه فعلا کار نمیکنه، از برنامه جانبی برای حذف در دیتابیس استفاده کنید.");
    // MainWindow window;
    // for (auto it = window.listOfItems.begin();it != window.listOfItems.end();++it)
    // {
    //     int id = (*it)->Id;
    //     window.mydb.exec(&"DELETE FROM infotable WHERE id = "[id]);
    //     // if (window.mydb.exec())
    //     // {
    //     //     QMessageBox::critical(this,"خطا","نمیتوان شناسه را دیتابیس پیدا کرد");
    //     //     return;
    //     // }
    //     it = window.listOfItems.erase(it);
    // }
}
