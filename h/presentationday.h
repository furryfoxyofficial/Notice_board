#ifndef PRESENTATIONDAY_H
#define PRESENTATIONDAY_H

#include <QDateTime>
#include <QFileDialog>
#include <QRandomGenerator>
#include <QDialog>
#include <QMessageBox>

#include "applicationitems.h"

namespace Ui {
class PresentationDay;
}

class PresentationDay : public QDialog
{
    Q_OBJECT

public:
    explicit PresentationDay(QWidget *parent = nullptr);
    ~PresentationDay();
    int GenerateId();

signals:
    void AddData(const ListItems &listofitems);

private slots:
    void on_Cancelbtn_clicked();
    void on_Okbtn_clicked();
    void on_Addressbtn_clicked();

private:
    Ui::PresentationDay *ui;
};

#endif // PRESENTATIONDAY_H
