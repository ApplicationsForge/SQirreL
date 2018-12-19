#include "sqlite_adapter.h"

SQLiteAdapter::SQLiteAdapter(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_dbLocalPath = "";
}

SQLiteAdapter::~SQLiteAdapter()
{
    close();
}

bool SQLiteAdapter::open(QString path)
{
    bool dbIsOpen = false;
    m_db.setDatabaseName(path);
    if(m_db.open())
    {
        dbIsOpen = true;
        m_dbLocalPath = path;
        //emit databaseIsNotOpen();
        //throw std::runtime_error("database is not connected");
    }
    return dbIsOpen;
    //QSqlQuery query;
    //qDebug() << query.exec("PRAGMA foreign_keys = ON;");
}

void SQLiteAdapter::close()
{
    m_db.close();
}

QSqlQuery SQLiteAdapter::runSQL(QString request)
{
    qDebug() << request;
    QString tmp = request;
    QSqlQuery query;
    if(query.prepare(tmp))
    {
        if(query.exec())
        {
            if(query.lastError().text() != " ")
            {
                qDebug() << query.lastError().text();
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Невозможно выполнить запрос!");
        }
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Невозможно подготовить запрос!");
    }
    return query;
}

QString SQLiteAdapter::dbLocalPath() const
{
    return m_dbLocalPath;
}
