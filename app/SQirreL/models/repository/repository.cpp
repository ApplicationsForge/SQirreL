#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent)
{
}

Repository::~Repository()
{
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
    return m_databasePath;
}

QString Repository::getDatabasePath() const
{
    return m_databasePath;
}

void Repository::setDatabasePath(const QString &databasePath)
{
    m_databasePath = databasePath;
}

void Repository::setDatabaseType(Repository::DB_TYPE type)
{
    m_currentAdapter = type;
}

QSqlQuery Repository::executeSQL(QString request)
{
    QSqlQuery result;
    switch (m_currentAdapter) {
    case DB_TYPE::SQLite:
    {
        try
        {
            SQLiteAdapter adapter(this);
            result = adapter.runSQL(m_databasePath, request);
        }
        catch(std::runtime_error e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return result;
}
