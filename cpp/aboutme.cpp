#include "aboutme.h"
#include "ui_aboutme.h"

AboutMe::AboutMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMe)
{
    setFixedSize(400,168);
    ui->setupUi(this);
    ui->GitLink->setOpenExternalLinks(true);
    ui->GitLink->setText("<a href='https://github.com/JavadRahmani2003'>مشخصات دقیق توسعه دهنده برنامه</a>");
}

AboutMe::~AboutMe()
{
    delete ui;
}
