#include "presentationday.h"
#include "ui_presentationday.h"

PresentationDay::PresentationDay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PresentationDay)
{
    ui->setupUi(this);
}

PresentationDay::~PresentationDay()
{
    delete ui;
}

int PresentationDay::GenerateId()
{
    std::uniform_int_distribution dist(1000,9999);
    return dist(*QRandomGenerator::global());
}

void PresentationDay::on_Cancelbtn_clicked()
{
    this->close();
    this->deleteLater();
}

void PresentationDay::on_Okbtn_clicked()
{
    ListItems listofitems;
    listofitems.Id = GenerateId();
    listofitems.DayName = ui->Day->currentText();
    listofitems.Time = ui->Time->time();
    listofitems.EndTime = ui->EndTime->time();
    listofitems.FileAddress = ui->Addresstxt->text();
    emit AddData(listofitems);
    this->accept();
}

void PresentationDay::on_Addressbtn_clicked()
{
    ui->Addresstxt->setText(QFileDialog::getOpenFileName(this,"آدرس فایل را وارد کنید",QCoreApplication::applicationDirPath(),"All files(*.*)"));
}

