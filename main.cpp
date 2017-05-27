#include "mainform.h"
#include <QApplication>
#include <QtSql>
#include <cstdlib>
#include <QtWidgets>

void createTables(const QString &sqlLine) {
    QSqlQuery query;
    query.exec(sqlLine);    
}

void createDatabase() {
    QFile f(":/resources/dbschema/db.schema");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << QObject::tr("cannot open resource file");
    QTextStream in(&f);
    QString line;
    QString sqlStatement = "";
    while (!in.atEnd()){
        line = in.readLine();
        if(line.startsWith('#') || line.isEmpty())
            continue;
        sqlStatement += line;
        if(sqlStatement.trimmed().endsWith(";")){
            createTables(sqlStatement);
            sqlStatement = "";
        }
    }
}

void processSchema()
{
    QProgressDialog progress;
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle(QObject::tr("SIGA"));
    progress.setLabelText(QObject::tr("Criando banco de dados..."));
    progress.setMinimum(0);
    progress.setMaximum(3);
    progress.setValue(1);
    qApp->processEvents();

    createDatabase();

    progress.setValue(2);
    qApp->processEvents();
    progress.setValue(3);
    qApp->processEvents();

    progress.setValue(progress.maximum());
    qApp->processEvents();
}

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("siga.dat");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bool existingData = QFile::exists("siga.dat");
    if (!existingData)
        if (!createConnection())
            return 1;
        else
            processSchema();
    else
        if (!createConnection())
            return 1;

    QTranslator *appTranslator = new QTranslator;
    appTranslator->load("translate_" + QLocale::system().name(), ":/translations");
    app.installTranslator(appTranslator);

    MainForm w(appTranslator);
    w.showMaximized();

    return app.exec();
}
