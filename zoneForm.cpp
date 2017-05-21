#include <QtWidgets>
#include <QtSql>
#include "zoneForm.h"
#include <QDebug>

ZoneForm::ZoneForm(double mlimit, double startrepvol, double maxrepvol, int reservid, int zoneid, QWidget *parent)
    : QDialog(parent),mlimit(mlimit),startRepVol(startrepvol),maxRepVol(maxrepvol),
      reservId(reservid), zoneId(zoneid)
{    
    MainForm *mainForm = static_cast<MainForm*>(parent);
    QSize size = QSize(25,25);

    repositoryComboBox = new QComboBox;
    repositoryLabel = new QLabel(tr("Reservatorio:"));
    repositoryLabel->setBuddy(repositoryComboBox);

    minLimitEdit = new QLineEdit;
    minLimitEdit->setLocale(QLocale::English);
    minLimitEdit->setText(QString::number(mlimit));
    minLimitEdit->setReadOnly(true);
    minLimitLabel = new QLabel(tr("Limite Inferior(hm³):"));
    minLimitLabel->setBuddy(minLimitEdit);

    maxLimitEdit = new QLineEdit;
    maxLimitEdit->setLocale(QLocale::English);
    connect(maxLimitEdit,SIGNAL(editingFinished()), this, SLOT(maxLimitValidate()));
    maxLimitLabel = new QLabel(tr("Limite Superior(hm³):"));
    maxLimitLabel->setBuddy(maxLimitEdit);

    priorityEdit = new QLineEdit;
    priorityEdit->setValidator(new QIntValidator(0, 99999, this));
    priorityLabel = new QLabel(tr("Prioridade:"));
    priorityLabel->setBuddy(priorityEdit);

    addButton = new QPushButton(tr("&Incluir"));
    addButton->setIcon(QIcon(":/resources/images/add.png"));
    addButton->setMinimumSize(size); addButton->setIconSize(size);
    deleteButton = new QPushButton(tr("&Apagar"));
    deleteButton->setIcon(QIcon(":/resources/images/remove.png"));
    deleteButton->setMinimumSize(size); deleteButton->setIconSize(size);
    saveButton = new QPushButton(tr("&Salvar"));
    saveButton->setIcon(QIcon(":/resources/images/ok.png"));
    saveButton->setMinimumSize(size); saveButton->setIconSize(size);
    closeButton = new QPushButton(tr("&Fechar"));
    closeButton->setIcon(QIcon(":/resources/images/btn_close.png"));
    closeButton->setMinimumSize(size); closeButton->setIconSize(size);

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(saveButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);    
    buttonBox->addButton(closeButton, QDialogButtonBox::AcceptRole);

    tableModel = new QSqlRelationalTableModel(this);
    tableModel->setTable("zonas");
    tableModel->setRelation(Zone_ReservId,
                            QSqlRelation("reservatorios", "id", "id"));
    tableModel->setSort(Zone_Priority, Qt::AscendingOrder);
    tableModel->setFilter(QString("reservid = %1").arg(reservid));
    tableModel->select();

    if (tableModel->rowCount()==0)
        insertionMode = true;

    QSqlTableModel *relationModel = tableModel->relationModel(Zone_ReservId);
    repositoryComboBox->setModel(relationModel);
    repositoryComboBox->setModelColumn(relationModel->fieldIndex("id"));
    repositoryComboBox->setDisabled(true);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(tableModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(minLimitEdit, Zone_MinVol);
    mapper->addMapping(maxLimitEdit, Zone_MaxVol);
    mapper->addMapping(priorityEdit, Zone_Priority);
    mapper->addMapping(repositoryComboBox, Zone_ReservId);

    if (zoneid != -1) {
        for (int row = 0; row < tableModel->rowCount(); ++row) {
            QSqlRecord record = tableModel->record(row);
            if (record.value(Zone_Id).toInt() == zoneid) {
                mapper->setCurrentIndex(row);
                break;
            }
        }
    } else {
        mapper->toFirst();
    }

    connect(addButton, SIGNAL(clicked()), this, SLOT(addZone()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteZone()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveZone()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(mapper->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), mainForm, SLOT(updateZoneView()));

    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    topButtonLayout->setContentsMargins(20, 0, 20, 5);
    topButtonLayout->addStretch();

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(repositoryLabel, 1, 0);
    mainLayout->addWidget(repositoryComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(minLimitLabel, 2, 0);
    mainLayout->addWidget(minLimitEdit, 2, 1, 1, 2);
    mainLayout->addWidget(maxLimitLabel, 3, 0);
    mainLayout->addWidget(maxLimitEdit, 3, 1);
    mainLayout->addWidget(priorityLabel, 4, 0);
    mainLayout->addWidget(priorityEdit, 4, 1, 1, 2);
    mainLayout->addWidget(buttonBox, 7, 0, 1, 3);
    mainLayout->setRowMinimumHeight(6, 10);
    mainLayout->setRowStretch(6, 1);
    mainLayout->setColumnStretch(2, 1);
    setLayout(mainLayout);

    //Tab order
    QDialog::setTabOrder(maxLimitEdit, priorityEdit);

    maxLimitEdit->setFocus();

    setWindowTitle(tr("Incluir/Editar Zonas e Prioridades"));
}

void ZoneForm::done(int result)
{
    if (tableModel->rowCount()==1){
        int v2,v3;
        int index = mapper->currentIndex();
        if (index!=-1) {
            QSqlRecord record = tableModel->record(index);
            v2 = record.value(Zone_MaxVol).toInt();
            v3 = record.value(Zone_Priority).toInt();
            if (v2|v3==0) {
                tableModel->removeRow(index);
                tableModel->select();
            }
        }
    }
    insertionMode = insertionMode?!insertionMode:insertionMode;
    QDialog::done(result);
}

void ZoneForm::saveZone() {    
    if (priorityValidate()) {
        mapper->submit();
        tableModel->submitAll();
        tableModel->select();
    }
}

void ZoneForm::maxLimitValidate() {
    QString str = maxLimitEdit->text();
    if (insertionMode && !str.isEmpty()) {
        double val = str.toDouble();
        double bottom = mlimit+0.01;
        if (val<=mlimit || val>startRepVol) {
            int r = QMessageBox::warning(this, tr("Valor inválido"),
                                         tr("Valor digitado está fora do range entre %1 e %2")
                                         .arg(QString::number(bottom))
                                         .arg(QString::number(startRepVol)), QMessageBox::Yes);
            maxLimitEdit->setFocus();
            maxLimitEdit->selectAll();
        }
    }
}

int ZoneForm::countPriorityRows(QString priority) {
    QSqlDatabase db=QSqlDatabase::database();
    QString sqlstr=QString("SELECT count(*) FROM zonas WHERE priority=\"%1\";")
                .arg(priority);
    QSqlQuery q(db); q.exec(sqlstr); q.next();
    return q.value(0).toInt();
}

bool ZoneForm::priorityValidate() {
    QString str = priorityEdit->text();
    if (insertionMode && !str.isEmpty()) {
        int rows = countPriorityRows(str);
        if (rows > 0) {
            int r = QMessageBox::warning(this, tr("Valor inválido"),
                                         tr("Valor de Prioridade digitado já cadastrado!"), QMessageBox::Yes);
            priorityEdit->setFocus();
            priorityEdit->selectAll();
            return false;
        }
    }
    return true;
}

void ZoneForm::addZone()
{    
    insertionMode = true;
    mapper->toLast();
    int row = mapper->currentIndex();
    if (row!=-1) {
        QSqlRecord record = tableModel->record(row);
        mlimit = record.value(Zone_MaxVol).toDouble();
    }

    mapper->submit();
    tableModel->insertRow(row);
    mapper->setCurrentIndex(row);

    if (mlimit!=0.0){
        minLimitEdit->setText(QString::number(mlimit));
    }

    maxLimitEdit->clear();
    priorityEdit->clear();
    maxLimitEdit->setFocus();
}

void ZoneForm::deleteZone()
{
    insertionMode = false;
    int current = mapper->currentIndex();
    mapper->toLast();
    int row = mapper->currentIndex();
    tableModel->removeRow(row);
    mapper->submit();
    tableModel->select();
    mapper->setCurrentIndex(qMin(current, tableModel->rowCount() - 1));
    insertionMode = true;
}
