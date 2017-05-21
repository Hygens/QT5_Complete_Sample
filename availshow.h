#ifndef AVAILSHOW_H
#define AVAILSHOW_H

#include <QtWidgets>
#include <QDialog>
#include "priorityZone.h"
#include <vector>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class AvailShow;
}

class AvailShow : public QDialog
{
    Q_OBJECT

public:
    explicit AvailShow(QWidget *parent = 0);
    ~AvailShow();
    void done(int result);
    void loadView(std::vector<PriorityZone *>);

private:    
    Ui::AvailShow *ui;
};

#endif // AVAILSHOW_H
