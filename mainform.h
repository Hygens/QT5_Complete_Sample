#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

#include "zoneForm.h"
#include "availshow.h"
#include "priorityUtils.h"
#include "lineediticonized.h"
#include "clicklabel.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QModelIndex;
class QPushButton;
class QSplitter;
class QSqlRelationalTableModel;
class QTableView;
class QLineEdit;
QT_END_NAMESPACE

enum {
    Repository_Id = 0,
    Repository_MinVol = 1,
    Repository_AvailVol = 2,
    Repository_MaxVol = 3
};

class MainForm : public QWidget
{
    Q_OBJECT

public:
    MainForm(QTranslator*);

protected:
    bool eventFilter(QObject*, QEvent*) override;

public slots:
    void updateZoneView();

private slots:    
    void addRepository();
    void deleteRepository();
    void editDataRepository();
    void saveDataRepository();
    void editZones();
    void searchZone();
    std::vector<PriorityZone *> disponibilidades();
    void importFromFile();
    void exportToFile();
    void validateCells(const QModelIndex&, const QModelIndex&);
    void validatePressed();
    void switchLanguage(QAction*);

private:
    void createRepositoryPanel();
    void createZonePanel();
    void initializeZones(double,int);
    void retranslateUi();
    QString openFile(int type);
    QModelIndex existsRepository(QString id);

    const int duration = 2000;
    const int OPEN_FILE = 1000;
    const int SAVE_FILE = 1001;    

    QSqlRelationalTableModel *repositoryModel;
    QSqlRelationalTableModel *zoneModel;
    QWidget *repositoryPanel;
    QWidget *zonePanel;
    QLabel *repositoryLabel;
    QLabel *zoneLabel;
    QLabel *brFlag;
    QLabel *euaFlag;
    QTableView *repositoryView;
    QTableView *zoneView;
    QSplitter *splitter;
    QPushButton *addButton;
    QPushButton *deleteRepButton;
    QPushButton *deleteZoneButton;
    QPushButton *saveButton;
    QPushButton *updateButton;
    QPushButton *exportButton;
    QPushButton *importButton;
    QPushButton *editButton;
    QPushButton *availButton;
    QPushButton *quitButton;
    LineEditIconized *searchEdit;
    QDialogButtonBox *buttonBoxForm;
    QWidget *boxButtonsRepository;
    QWidget *boxButtonsZone;
    bool invalidValue=false;
    QTranslator *appTranslator;
};

#endif
