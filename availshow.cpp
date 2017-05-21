#include "availshow.h"
#include "ui_availshow.h"

AvailShow::AvailShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvailShow)
{
    ui->setupUi(this);
    ui->availShowView->resizeColumnsToContents();
    ui->availShowView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->availShowCloseButton, SIGNAL(clicked()),this,SLOT(accept()));
}

AvailShow::~AvailShow()
{
    delete ui;
}

void AvailShow::done(int result) {
    QDialog::done(result);
}

void AvailShow::loadView(std::vector<PriorityZone*> list) {
    QStandardItemModel *model = new QStandardItemModel(list.size(),2,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("Priority")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Volume Disponível(hm³)")));
    for(int i = 0; i < list.size() ; i++)
    {
        PriorityZone *pzone = static_cast<PriorityZone*>(list[i]);
        model->setItem(i,0,new QStandardItem(QString::number(pzone->getPriority())));
        model->setItem(i,1,new QStandardItem(QString::number(pzone->getAvailableVolume())));
    }
    ui->availShowView->setModel(model);
}
