#include "showallintable.h"
#include "ui_showallintable.h"

ShowAllInTable::ShowAllInTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShowAllInTable)
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    connect(timer,&QTimer::timeout,this,&ShowAllInTable::autoScroll);
    connect(ui->ExcelTable->horizontalHeader(),&QHeaderView::sectionDoubleClicked,this,&ShowAllInTable::resizeColumn);
    connect(ui->ExcelTable->verticalHeader(),&QHeaderView::sectionDoubleClicked,this,&ShowAllInTable::resizeRow);
    pix.load(":/IconApp/Logo-in-App.jpg");
    ui->image->setPixmap(pix);
    ui->banner->setText("مقدمه دانشجویان گرامی را به دانشگاه آزاد گرامی میداریم");
    Animation = new QPropertyAnimation(ui->banner,"geometry");
    Animation->setDuration(2000);
    Animation->setStartValue(QRect(-this->width(),0,this->width(),60));
    Animation->setEndValue(QRect(this->width(), 0, this->width(), 60));
    Animation->setEasingCurve(QEasingCurve::Linear);
    Animation->start();
    connect(Animation,&QPropertyAnimation::finished,this,&ShowAllInTable::restartAnimation);
}

ShowAllInTable::~ShowAllInTable()
{
    delete ui;
}

void ShowAllInTable::runExcel(QString &fileformat)
{
    QXlsx::Document doc(fileformat);
    if (!doc.load()) {
        qDebug() << "there is an error!";
    }

    QStringList header = {"کد ارائه","نام درس","شماره کلاس","نام استاد","ساعت"};

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(header);
    for (int row = 1; row <= doc.dimension().lastRow(); ++row) {
        for (int col = 1; col <= doc.dimension().lastColumn(); ++col) {
            auto cell = doc.cellAt(row, col);
            QString cellval = cell ? cell->value().toString() : "";
            if (cellval.length() > 20) {
                cellval.replace(" ", "\n"); // Replace spaces with new lines for demonstration
            }
            QStandardItem *item = new QStandardItem(cellval);
            model->setItem(row - 1, col - 1, item);
        }
    }

    ui->ExcelTable->setModel(model);
    ui->ExcelTable->setWordWrap(true);

    // QFont headerFont = ui->ExcelTable->font();
    // headerFont.setPointSize(24); // Set the desired font size
    // headerFont.set;
    // ui->ExcelTable->horizontalHeader()->setFont(headerFont);

    // Set uniform column width and row height
    int uniformSize = 0; // This will hold the maximum size for both width and height

    for (int col = 0; col < model->columnCount(); ++col) {
        int maxWidth = 0;
        for (int row = 0; row < model->rowCount(); ++row) {
            QString cellText = model->item(row, col)->text();
            QFontMetrics metrics(ui->ExcelTable->font());
            int width = metrics.horizontalAdvance(cellText) + 10; // Add some padding
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
        ui->ExcelTable->setColumnWidth(col, maxWidth);

        // Update uniform size if this column's width is greater
        if (maxWidth > uniformSize) {
            uniformSize = maxWidth;
        }
    }

    const int maxHeight = 40; // Set your desired maximum height here
    for (int row = 0; row < model->rowCount(); ++row) {
        int maxHeightForRow = 0;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellText = model->item(row, col)->text();
            int height = cellText.count('\n') + 1; // Count lines for multi-line cells
            height *= ui->ExcelTable->font().pointSize(); // Adjust based on font size
            if (height > maxHeightForRow) {
                maxHeightForRow = height;
            }
        }
        // Set the maximum height for the row
        ui->ExcelTable->setRowHeight(row, std::min(maxHeightForRow, maxHeight));
    }

    // Finally, set the same height for all rows to keep them uniform
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->ExcelTable->setRowHeight(row, std::min(uniformSize, maxHeight));
    }

    for (int col = 0; col < model->columnCount(); ++col) {
        ui->ExcelTable->resizeColumnToContents(col);
    }
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->ExcelTable->resizeRowToContents(row);
    }
}

void ShowAllInTable::startAutoScroll()
{
    timer->start(5000);
}

void ShowAllInTable::autoScroll()
{
    auto bar = ui->ExcelTable->verticalScrollBar();
    bar->setValue(bar->value() + 1);
    if (bar->value() >= bar->maximum())
    {
        bar->setValue(0);
    }
}

void ShowAllInTable::resizeColumn(int column)
{
    ui->ExcelTable->resizeColumnToContents(column);
}

void ShowAllInTable::resizeRow(int row)
{
    ui->ExcelTable->resizeRowToContents(row);
}

void ShowAllInTable::restartAnimation()
{
    ui->banner->setGeometry(QRect(-this->width(), 0, this->width(), 60)); // Reset to the start position
    Animation->start(); // Start the animation again
}
