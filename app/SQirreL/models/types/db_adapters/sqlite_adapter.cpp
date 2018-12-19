#include "sqlite_adapter.h"

SQLiteAdapter::SQLiteAdapter(QObject *parent) : QObject(parent)
{
}

SQLiteAdapter::~SQLiteAdapter()
{

}

QSqlQuery SQLiteAdapter::runSQL(QString dbPath, QString request)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if(!db.open())
    {
       throw std::runtime_error("database is not connected");
    }

    qDebug() << request;
    QSqlQuery query;
    if(query.prepare(request))
    {
        if(query.exec())
        {
            if(query.lastError().text() != " ")
            {
                //qDebug() << query.lastError().text();
                throw std::runtime_error(query.lastError().text().toStdString());
            }
        }
        else
        {
            throw std::runtime_error("Невозможно выполнить запрос!");
            //QMessageBox(QMessageBox::Warning, "Ошибка", "Невозможно выполнить запрос!").exec();
        }
    }
    else
    {
        throw std::runtime_error("Невозможно подготовить запрос!");
        //QMessageBox(QMessageBox::Warning, "Ошибка", "Невозможно подготовить запрос!").exec();
    }

    /*QString qs;
    {
        qs.append(QSqlDatabase::database().connectionName());
    }
    QSqlDatabase::removeDatabase(qs);*/

    QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
    qDebug() << "AfterDelete" << QSqlDatabase::database().connectionNames();

    return query;
}
