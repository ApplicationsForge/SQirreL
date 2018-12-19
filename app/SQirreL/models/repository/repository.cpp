#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent)
{
}

Repository::~Repository()
{
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
