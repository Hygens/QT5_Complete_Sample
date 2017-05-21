#ifndef ZoneFORM_H
#define ZoneFORM_H

#include <QDialog>
#include <QMouseEvent>
#include <QEvent>
#include <mainform.h>

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
class QDialogButtonBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSqlRelationalTableModel;
QT_END_NAMESPACE

enum {
    Zone_Id = 0,
    Zone_MinVol = 1,
    Zone_MaxVol = 2,
    Zone_Priority = 3,
    Zone_ReservId = 4
};

class ZoneForm : public QDialog
{
    Q_OBJECT

public:
    ZoneForm(double mlimit, double startrepvol,
             double maxrepvol, int reservid,
             int zoneid, QWidget *parent = 0);
    void done(int result);    

private slots:
    void addZone();
    void deleteZone();
    void maxLimitValidate();
    bool priorityValidate();
    void saveZone();

private:
    int countPriorityRows(QString priority);

    QSqlRelationalTableModel *tableModel;
    QDataWidgetMapper *mapper;
    QLabel *minLimitLabel;
    QLabel *maxLimitLabel;
    QLabel *priorityLabel;
    QLabel *repositoryLabel;
    QComboBox *repositoryComboBox;
    QLineEdit *minLimitEdit;
    QLineEdit *maxLimitEdit;
    QLineEdit *priorityEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *closeButton;
    QPushButton *saveButton;
    QDialogButtonBox *buttonBox;
    double maxRepVol;
    double mlimit;
    double startRepVol;
    double reservId;
    double zoneId;
    bool insertionMode = false;
    int duration;
};
#endif
