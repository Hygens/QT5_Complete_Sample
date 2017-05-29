#include "mainform.h"

MainForm::MainForm(QTranslator *appTrans): appTranslator(appTrans)
{
    QSize size = QSize(40,40);
    addButton = new QPushButton();
    addButton->setIcon(QIcon(":/resources/images/add.png"));
    addButton->setToolTip(tr("Incluir Reservatório e Zonas"));
    addButton->setToolTipDuration(duration);
    addButton->setMinimumSize(size); addButton->setIconSize(size);

    deleteRepButton = new QPushButton();
    deleteRepButton->setToolTip(tr("Apagar Reservatório e Zonas"));
    deleteRepButton->setToolTipDuration(duration);
    deleteRepButton->setIcon(QIcon(":/resources/images/remove.png"));
    deleteRepButton->setMinimumSize(size); deleteRepButton->setIconSize(size);

    updateButton = new QPushButton();
    updateButton->setIcon(QIcon(":/resources/images/editor.png"));
    updateButton->setToolTip(tr("Editar Reservatório"));
    updateButton->setToolTipDuration(duration);
    updateButton->setMinimumSize(size); updateButton->setIconSize(size);

    saveButton = new QPushButton();
    saveButton->setIcon(QIcon(":/resources/images/ok.png"));
    saveButton->setToolTip(tr("Salvar dados na base de Reservatórios"));
    saveButton->setMinimumSize(size); saveButton->setIconSize(size);

    exportButton = new QPushButton();
    exportButton->setIcon(QIcon(":/resources/images/export.png"));
    exportButton->setToolTip(tr("Exportar dados para arquivo de um Repositório e Zonas"));
    exportButton->setMinimumSize(size); exportButton->setIconSize(size);
    exportButton->setDisabled(true);

    importButton = new QPushButton();
    importButton->setIcon(QIcon(":/resources/images/import.png"));
    importButton->setToolTip(tr("Importar dados para arquivo de um Repositório e Zonas"));
    importButton->setMinimumSize(size); importButton->setIconSize(size);

    saveButton = new QPushButton();
    saveButton->setIcon(QIcon(":/resources/images/ok.png"));
    saveButton->setToolTip(tr("Salvar dados na base de Reservatórios"));
    saveButton->setMinimumSize(size); saveButton->setIconSize(size);

    availButton = new QPushButton();
    availButton->setIcon(QIcon(":/resources/images/report.png"));
    availButton->setToolTip(tr("Disponibilidade por Repositório e Zonas"));
    availButton->setToolTipDuration(duration);
    availButton->setMinimumSize(size); availButton->setIconSize(size);

    editButton = new QPushButton();
    editButton->setToolTip(tr("Formulário para Editar/Incluir Zona"));
    editButton->setToolTipDuration(duration);
    editButton->setIcon(QIcon(":/resources/images/add.png"));
    editButton->setMinimumSize(size); editButton->setIconSize(size);

    searchEdit = new LineEditIconized(QIcon(":/resources/images/search.png"),this);
    searchEdit->setToolTip(tr("Pesquisa Zona por Prioridade"));
    searchEdit->setToolTipDuration(duration);
    searchEdit->setMaximumSize(QSize(120,searchEdit->height()));

    quitButton = new QPushButton();
    size = QSize(128,40);
    quitButton->setIcon(QIcon(":/resources/images/exit.png"));
    quitButton->setToolTip(tr("Fechar a aplicação"));
    quitButton->setToolTipDuration(duration);
    quitButton->setMinimumSize(size); quitButton->setIconSize(size);

    boxButtonsRepository = new QWidget;
    QHBoxLayout *panel1Layout = new QHBoxLayout;
    panel1Layout->addWidget(addButton);
    panel1Layout->addWidget(updateButton);
    panel1Layout->addWidget(saveButton);
    panel1Layout->addWidget(deleteRepButton);
    panel1Layout->addWidget(exportButton);
    panel1Layout->addWidget(importButton);
    panel1Layout->addWidget(availButton);
    panel1Layout->setSpacing(0);
    panel1Layout->addStretch();
    boxButtonsRepository->setLayout(panel1Layout);

    boxButtonsZone = new QWidget;
    QHBoxLayout *panel2Layout = new QHBoxLayout;
    panel2Layout->addWidget(editButton);
    panel2Layout->addStretch();
    panel2Layout->addWidget(searchEdit);
    panel2Layout->setSpacing(0);
    boxButtonsZone->setLayout(panel2Layout);

    createRepositoryPanel();
    createZonePanel();

    splitter = new QSplitter(Qt::Vertical);
    splitter->setFrameStyle(QFrame::StyledPanel);
    splitter->addWidget(repositoryPanel);
    splitter->addWidget(zonePanel);

    buttonBoxForm = new QDialogButtonBox;
    buttonBoxForm->addButton(quitButton, QDialogButtonBox::AcceptRole);
    buttonBoxForm->setCenterButtons(true);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addRepository()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(editDataRepository()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveDataRepository()));
    connect(deleteRepButton, SIGNAL(clicked()), this, SLOT(deleteRepository()));
    connect(availButton,&QPushButton::clicked, this, [this](){
        AvailShow form(this);
        form.loadView(this->disponibilidades());
        form.exec();
    });
    connect(editButton, SIGNAL(clicked()), this, SLOT(editZones()));
    connect(searchEdit,SIGNAL(returnPressed()),this,SLOT(searchZone()));
    connect(exportButton,SIGNAL(clicked()),this,SLOT(exportToFile()));
    connect(importButton,SIGNAL(clicked()),this,SLOT(importFromFile()));
    connect(repositoryView, &QTableView::pressed,this,[this](){ exportButton->setDisabled(false); });
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    mainLayout->addWidget(buttonBoxForm);
    setLayout(mainLayout);

    setWindowTitle(tr("RESERVATÓRIOS, ZONAS, PRIORIDADES E DISPONIBILIDADES"));
    setStyleSheet( "background-image:url(:/resources/images/cachoeira.jpg);" );
    setAutoFillBackground(true);
    repositoryView->setCurrentIndex(repositoryModel->index(0, 0));
}

void MainForm::retranslateUi() {
    addButton->setToolTip(tr("Incluir Reservatório e Zonas"));
    deleteRepButton->setToolTip(tr("Apagar Reservatório e Zonas"));
    updateButton->setToolTip(tr("Editar Reservatório"));
    saveButton->setToolTip(tr("Salvar dados na base de Reservatórios"));
    exportButton->setToolTip(tr("Exportar dados para arquivo de um Repositório e Zonas"));
    importButton->setToolTip(tr("Importar dados para arquivo de um Repositório e Zonas"));
    saveButton->setToolTip(tr("Salvar dados na base de Reservatórios"));
    availButton->setToolTip(tr("Disponibilidade por Repositório e Zonas"));
    editButton->setToolTip(tr("Formulário para Editar/Incluir Zona"));
    searchEdit->setToolTip(tr("Pesquisa Zona por Prioridade"));
    quitButton->setToolTip(tr("Fechar a aplicação"));

    repositoryLabel ->setText(tr("Reservatórios"));
    repositoryModel->setHeaderData(Repository_AvailVol,
                                   Qt::Horizontal, tr("Volume Inicial(hm³)"));
    repositoryModel->setHeaderData(Repository_MinVol,
                                   Qt::Horizontal, tr("Volume Mínimo(hm³)"));
    repositoryModel->setHeaderData(Repository_MaxVol,
                                   Qt::Horizontal, tr("Volume Máximo(hm³)"));
    repositoryView->setToolTip(tr("Selecione a linha desejada..."));

    zoneModel->setHeaderData(Zone_MinVol, Qt::Horizontal, tr("Limite Inferior(hm³)"));
    zoneModel->setHeaderData(Zone_MaxVol, Qt::Horizontal, tr("Limite Superior(hm³)"));
    zoneModel->setHeaderData(Zone_Priority, Qt::Horizontal, tr("Prioridade"));
    zoneView->setToolTip(tr("Selecione a linha desejada..."));

    zoneLabel ->setText(tr("Zonas"));

    setWindowTitle(tr("RESERVATÓRIOS, ZONAS, PRIORIDADES E DISPONIBILIDADES"));
}

QString MainForm::openFile(int type) {
    QString selectedFilter;
    QString fileName;
    if (this->SAVE_FILE==type)
    {
        fileName = QFileDialog::getSaveFileName(this,
                                                tr("Arquivo a exportar..."),
                                                QString(),
                                                tr("All Files (*);;Text Files (*.txt)"),
                                                &selectedFilter);
    }
    else
    {
        fileName = QFileDialog::getOpenFileName(this,
                                                tr("Arquivo a importar..."),
                                                QString(),
                                                tr("All Files (*);;Text Files (*.txt)"),
                                                &selectedFilter);

    }
    return fileName;
}

void MainForm::importFromFile() {
    QString fileName = openFile(OPEN_FILE);
    QFile file(fileName);
    QStringList strList;
    int row = 0;
    if (file.open(QIODevice::ReadOnly)){
        QString line = file.readLine();
        strList = line.split(" ");
        QModelIndex index = existsRepository(strList.at(0));
        if (index.isValid()) {
            for (int i = 1; i<4; i++) {
                QTableWidgetItem *test = new QTableWidgetItem(strList.at(i));
                repositoryModel->setData(repositoryModel->index(row,i),strList.at(i));
            }
            repositoryModel->submitAll();
        } else {
            repositoryModel->insertRow(row);
            for (int i = 1; i<4; i++) {
                repositoryModel->setData(zoneModel->index(row,i), strList.at(i).trimmed());
            }
            repositoryModel->submitAll();
        }
        row = 0;
        while (!file.atEnd()){
            QString line = file.readLine();
            strList = line.split(" ");
            zoneModel->insertRow(row);
            for (int x = 1; x < strList.size(); x++){
                zoneModel->setData(zoneModel->index(row,x), strList.at(x).trimmed());
            }
            zoneModel->submit();
            row++;
        }
    }
    updateZoneView();
    file.close();
}

void MainForm::exportToFile()
{
    QString fileName = openFile(SAVE_FILE);

    QFile f( fileName );
    if( f.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &f );
        QModelIndex index = repositoryView->currentIndex();
        QSqlRecord record = repositoryModel->record(index.row());
        QStringList strList;
        strList << record.value(Repository_Id).toString();
        strList << record.value(Repository_MinVol).toString();
        strList << record.value(Repository_AvailVol).toString();
        strList << record.value(Repository_MaxVol).toString();
        ts << strList.join(" ") + "\n";
        for (int i=0; i<zoneModel->rowCount(); i++)
        {
            strList.clear();

            for (int j=0; j<zoneModel->columnCount(); j++)
                strList << zoneModel->data(zoneModel->index(i,j)).toString();

            ts << strList.join(" ") + "\n";
        }
        f.close();
    }
    exportButton->setDisabled(true);
}


void MainForm::updateZoneView()
{
    QModelIndex index = repositoryView->currentIndex();
    if (index.isValid()) {
        QSqlRecord record = repositoryModel->record(index.row());
        int id = record.value("id").toInt();
        zoneModel->setFilter(QString("reservid = %1").arg(id));
        zoneLabel->setText(tr("Zonas e Prioridades no Reservatório Selecionado"));
    } else {
        zoneModel->setFilter("reservid = -1");
        zoneLabel->setText(tr("Zonas"));
    }
    zoneModel->select();
    zoneView->horizontalHeader()->setVisible(true);
}

QModelIndex MainForm::existsRepository(QString id) {
    QAbstractItemModel *mdl = repositoryView->model();
    QSortFilterProxyModel proxy;
    proxy.setSourceModel(mdl);
    proxy.setFilterKeyColumn(0);
    proxy.setFilterFixedString(id.trimmed());
    return proxy.mapToSource(proxy.index(0,0));
}

void MainForm::searchZone() {
    QAbstractItemModel *mdl = zoneView->model();
    QSortFilterProxyModel proxy;
    proxy.setSourceModel(mdl);
    proxy.setFilterKeyColumn(3);
    proxy.setFilterFixedString(searchEdit->text().trimmed());
    QModelIndex index = proxy.mapToSource(proxy.index(0,0));
    zoneView->selectRow(index.row());
    searchEdit->clear();
}

void MainForm::editDataRepository() {
    QModelIndex row = repositoryView->currentIndex();
    repositoryView->edit(row);
}

void MainForm::saveDataRepository() {    
    repositoryModel->submitAll();
    repositoryModel->select();
}

void MainForm::addRepository()
{
    int row = repositoryModel->rowCount();
    repositoryModel->insertRow(row);
    QModelIndex index = repositoryModel->index(row, Repository_MinVol);
    repositoryView->setCurrentIndex(index);
    repositoryView->edit(index);
}

void MainForm::deleteRepository()
{
    QModelIndex index = repositoryView->currentIndex();
    if (!index.isValid())
        return;

    QSqlDatabase::database().transaction();
    QSqlRecord record = repositoryModel->record(index.row());
    int id = record.value(Repository_Id).toInt();
    int numZones = 0;

    QSqlQuery query(QString("SELECT COUNT(*) FROM zonas "
                            "WHERE reservid = %1").arg(id));
    if (query.next())
        numZones = query.value(0).toInt();
    if (numZones > 0) {
        int r = QMessageBox::warning(this, tr("Apagar reservatório"),
                                     tr("Apagar %1 e todas as suas zonas?")
                                     .arg(record.value(Repository_Id).toString()),
                                     QMessageBox::Yes | QMessageBox::No);
        if (r == QMessageBox::No) {
            QSqlDatabase::database().rollback();
            return;
        }

        query.exec(QString("DELETE FROM zonas "
                           "WHERE reservid = %1").arg(id));
    }

    repositoryModel->removeRow(index.row());
    repositoryModel->submitAll();
    QSqlDatabase::database().commit();

    updateZoneView();
    repositoryView->setFocus();
}

void MainForm::validatePressed() {
    QModelIndex index = repositoryView->currentIndex();
    int col = index.column();
    int row = index.row();
    double maxvol = repositoryView->model()->data(repositoryView->model()->index(row,3)).toDouble();
    if((col==2 && maxvol>0.0) || col == 3)
    {
        double minvol = repositoryView->model()->data(repositoryView->model()->index(row,1)).toDouble();
        double availvol = repositoryView->model()->data(repositoryView->model()->index(row,2)).toDouble();
        if (availvol<=minvol || availvol >maxvol) {
            int r = QMessageBox::warning(this, tr("Dado inválido"),
                                         tr("Corrija o valor do volume inicial que deve ser maior que o mínimo "
                                            "e menor ou igual ao máximo!!!"),
                                         QMessageBox::Yes);
            if (col==2) {
                invalidValue=true;
                repositoryModel->submit();
                repositoryModel->select();
            }
            QModelIndex index = repositoryView->model()->index(row, 2);
            repositoryView->setCurrentIndex(index);
            repositoryView->selectionModel()->select( index,
                                                      QItemSelectionModel::ClearAndSelect );
            repositoryView->edit(index);
        }
    }
}

void MainForm::initializeZones(double minvol, int reservid) {
    QSqlDatabase db=QSqlDatabase::database();
    QString sqlstr=QString("INSERT INTO zonas (minvol,reservid) VALUES(\"%1\",\"%2\");")
            .arg(QString::number(minvol))
            .arg(QString::number(reservid));
    QSqlQuery q(db);
    if(q.exec(sqlstr)==false)
    {
        QMessageBox *pmsg = new QMessageBox;
        pmsg->setText(tr("Erro na gravação de dados na tabela zones."));
        pmsg->setInformativeText(q.lastError().text());
        pmsg->exec();
        return;
    }
    db.commit();
}

void MainForm::editZones()
{
    int zoneId = -1; int reservId = -1;
    double minrepvol=0.0,startrepvol=0.0,maxrepvol=0.0,mlimit = 0.0;
    QModelIndex index = repositoryView->currentIndex();
    if (index.isValid()) {
        QSqlRecord record = repositoryModel->record(index.row());
        reservId = record.value(Repository_Id).toInt();
        minrepvol = record.value(Repository_MinVol).toDouble();
        startrepvol = record.value(Repository_AvailVol).toDouble();
        maxrepvol = record.value(Repository_MaxVol).toDouble();
    }

    index = zoneView->currentIndex();
    if (index.isValid()) {
        QSqlRecord record = zoneModel->record(index.row());
        zoneId = record.value(Zone_Id).toInt();
        mlimit = record.value(Zone_MaxVol).toDouble();
    }

    if (zoneModel->rowCount()==0){
        initializeZones(mlimit>0.0?mlimit:minrepvol,reservId);
    }

    ZoneForm form(mlimit>0.0?mlimit:minrepvol,startrepvol,maxrepvol,reservId, zoneId, this);
    form.exec();
    updateZoneView();
}

void MainForm::createRepositoryPanel()
{
    repositoryPanel = new QWidget;

    repositoryModel = new QSqlRelationalTableModel(this);
    repositoryModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    repositoryModel->setTable("reservatorios");
    repositoryModel->setSort(Repository_Id, Qt::AscendingOrder);
    repositoryModel->setHeaderData(Repository_AvailVol,
                                   Qt::Horizontal, tr("Volume Inicial(hm³)"));
    repositoryModel->setHeaderData(Repository_MinVol,
                                   Qt::Horizontal, tr("Volume Mínimo(hm³)"));
    repositoryModel->setHeaderData(Repository_MaxVol,
                                   Qt::Horizontal, tr("Volume Máximo(hm³)"));
    repositoryModel->select();

    repositoryView = new QTableView;
    repositoryView->setModel(repositoryModel);
    repositoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    repositoryView->setSelectionBehavior(QAbstractItemView::SelectRows);
    repositoryView->setColumnHidden(Repository_Id, true);
    repositoryView->resizeColumnsToContents();
    repositoryView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    repositoryView->horizontalHeader()->setVisible(true);
    repositoryView->setLocale(QLocale::English);
    repositoryView->installEventFilter(this);
    repositoryView->setToolTip(tr("Selecione a linha desejada..."));
    repositoryView->setToolTipDuration(duration);

    repositoryLabel = new QLabel(tr("Reservatórios"));
    repositoryLabel->setFont(QFont("Helvetica [Cronyx]", 15, QFont::Bold));
    repositoryLabel->setBuddy(repositoryView);

    connect(repositoryView->selectionModel(),
            SIGNAL(currentRowChanged(const QModelIndex &,
                                     const QModelIndex &)),
            this, SLOT(updateZoneView()));
    connect(repositoryView->model(),
            SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            this, SLOT(validateCells(const QModelIndex&, const QModelIndex&)));
    connect(repositoryView,
            SIGNAL(pressed(QModelIndex)),
            this, SLOT(validatePressed()));

    QSize size = QSize(20,20);
    QWidget *subtitle = new QWidget;
    QLabel *euaFlag = new ClickLabel;
    QIcon pixmap = QIcon(":/resources/images/eua_flag.jpg");
    euaFlag->setPixmap(pixmap.pixmap(size));
    euaFlag->setMinimumSize(size);
    euaFlag->setToolTip(tr("English"));
    euaFlag->setToolTipDuration(2000);
    QAction *acten = new QAction();
    acten->setData(tr("en"));
    euaFlag->addAction(acten);
    connect(euaFlag,SIGNAL(clicked(QAction*)),this,SLOT(switchLanguage(QAction*)));
    QLabel *brFlag = new ClickLabel;
    QIcon pixmap1 = QIcon(":/resources/images/br_flag.jpg");
    brFlag->setPixmap(pixmap1.pixmap(size));
    brFlag->setMinimumSize(size);
    QAction *actbr = new QAction();
    actbr->setData(tr("pt"));
    brFlag->addAction(actbr);
    brFlag->setToolTip(tr("Portuguese"));
    brFlag->setToolTipDuration(2000);
    connect(brFlag,SIGNAL(clicked(QAction*)),this,SLOT(switchLanguage(QAction*)));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(repositoryLabel);
    hlayout->setSpacing(0);
    hlayout->addStretch();
    hlayout->addWidget(euaFlag);
    hlayout->addWidget(brFlag);
    subtitle->setLayout(hlayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(subtitle);
    layout->addWidget(boxButtonsRepository);
    layout->addWidget(repositoryView);
    repositoryPanel->setLayout(layout);
}

void MainForm::validateCells(const QModelIndex& topLeft, const QModelIndex& bottomRight) {
    int col = topLeft.column();
    int row = topLeft.row();
    double maxvol = repositoryView->model()->data(repositoryView->model()->index(row,3)).toDouble();
    if((col==2 && maxvol>0.0) || col == 3)
    {
        double minvol = repositoryView->model()->data(repositoryView->model()->index(row,1)).toDouble();
        double availvol = repositoryView->model()->data(repositoryView->model()->index(row,2)).toDouble();
        if (availvol<=minvol || availvol >maxvol) {
            int r = QMessageBox::warning(this, tr("Dado inválido"),
                                         tr("Corrija o valor do volume inicial que deve ser maior que o mínimo "
                                            "e menor ou igual ao máximo!!!"),
                                         QMessageBox::Yes);
            if (col==2) {
                invalidValue=true;
                repositoryModel->submit();
                repositoryModel->select();
            }
            QModelIndex index = repositoryView->model()->index(row, 2);
            repositoryView->setCurrentIndex(index);
            repositoryView->selectionModel()->select( index,
                                                      QItemSelectionModel::ClearAndSelect );
            repositoryView->edit(index);
        }
    }
}

void MainForm::createZonePanel()
{
    zonePanel = new QWidget;

    zoneModel = new QSqlRelationalTableModel(this);
    zoneModel->setTable("zonas");
    zoneModel->setRelation(Zone_ReservId,
                           QSqlRelation("reservatorios", "id", "id"));
    zoneModel->setSort(Zone_Priority, Qt::AscendingOrder);
    zoneModel->setHeaderData(Zone_MinVol, Qt::Horizontal, tr("Limite Inferior(hm³)"));
    zoneModel->setHeaderData(Zone_MaxVol, Qt::Horizontal, tr("Limite Superior(hm³)"));
    zoneModel->setHeaderData(Zone_Priority, Qt::Horizontal, tr("Prioridade"));

    zoneView = new QTableView;
    zoneView->setModel(zoneModel);
    zoneView->setSelectionMode(QAbstractItemView::SingleSelection);
    zoneView->setSelectionBehavior(QAbstractItemView::SelectRows);
    zoneView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    zoneView->resizeColumnsToContents();
    zoneView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    zoneView->setColumnHidden(Zone_Id, true);
    zoneView->setColumnHidden(Zone_ReservId, true);
    zoneView->setLocale(QLocale::English);
    zoneView->setToolTip(tr("Selecione a linha desejada..."));
    zoneView->setToolTipDuration(duration);

    zoneLabel = new QLabel(tr("Zonas"));
    zoneLabel->setFont(QFont("Helvetica [Cronyx]", 15, QFont::Bold));
    zoneLabel->setBuddy(zoneView);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(zoneLabel);
    layout->addWidget(boxButtonsZone);
    layout->addWidget(zoneView);
    zonePanel->setLayout(layout);
}

std::vector<PriorityZone *> MainForm::disponibilidades() {
    double minVol=0.0,availVol=0.0,maxVol=0.0; int id=-1;
    PriorityUtils *pUtils = new PriorityUtils();

    QModelIndex index = repositoryView->currentIndex();
    if (index.isValid()) {
        QSqlRecord record = repositoryModel->record(index.row());
        minVol = record.value(Repository_MinVol).toDouble();
        availVol = record.value(Repository_AvailVol).toDouble();
        maxVol = record.value(Repository_MaxVol).toDouble();
        id = record.value(Repository_Id).toInt();
    }

    zoneModel->setFilter(QString("reservid = %1").arg(id));
    zoneModel->select();
    int size = zoneModel->rowCount();
    std::vector<int> pArray;
    std::vector<double> vArray;
    for(int i=0;i<size;i++) {
        QSqlRecord record = zoneModel->record(i);
        int p = record.value(Zone_Priority).toInt();
        double plimit = record.value(Zone_MaxVol).toDouble();
        pArray.push_back(p);
        vArray.push_back(plimit);
    }

    std::vector<PriorityZone*> zones = pUtils->zonesAvailableSupply(
                pArray,vArray,minVol,maxVol,availVol);
    return zones;
}

bool MainForm::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == repositoryView)
    {
        if (event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Tab)
            {
                if (invalidValue)                {

                    keyEvent->ignore();
                    invalidValue=false;
                }
                return true;
            } else if (keyEvent->key() == Qt::Key_Return) {
                validatePressed();
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void MainForm::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();
    appTranslator->load("translate_" + locale, ":/translations");
    this->retranslateUi();
}

