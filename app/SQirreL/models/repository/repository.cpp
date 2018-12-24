#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_currentAdapter(SQLite),
    m_databasePath(""),
    m_currentCollectionPath(""),
    m_currentCollection("")
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

QString Repository::getCurrentCollectionPath() const
{
    return m_currentCollectionPath;
}

void Repository::setCurrentCollectionPath(const QString &currentCollectionPath)
{
    m_currentCollectionPath = currentCollectionPath;
    emit currentCollectionPathUpdated(m_currentCollectionPath);
}

Collection Repository::getCurrentCollection() const
{
    return m_currentCollection;
}

void Repository::setCurrentCollection(const Collection &currentCollection)
{
    m_currentCollection = currentCollection;
}
