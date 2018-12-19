#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_sqliteAdapter(new SQLiteAdapter(this))
{
}

Repository::~Repository()
{
    m_sqliteAdapter->close();
}

QString Repository::helloString() const
{
    return m_helloString;
}

void Repository::setHelloString(const QString &helloString)
{
    m_helloString = helloString;
}

QString Repository::getDBPath()
{
    return m_sqliteAdapter->dbLocalPath();
}

bool Repository::openSQLiteDatabase(QString localPath)
{
    m_currentAdapter = DB_TYPE::SQLite;
    return m_sqliteAdapter->open(localPath);
}

QSqlQuery Repository::getSQLResult(QString request)
{
    QSqlQuery result;
    switch (m_currentAdapter) {
    case DB_TYPE::SQLite:
    {
        result = m_sqliteAdapter->runSQL(request);
        break;
    }
    default:
    {
        break;
    }
    }
    return result;
}
