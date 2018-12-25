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

void Repository::addItem(CollectionItem item)
{
    m_currentCollection.addItem(item);

    SaveToFileInteractor saveToFile;
    CollectionToStringInteractor convertToString;
    saveToFile.execute(m_currentCollectionPath, convertToString.execute(m_currentCollection));

    emit currentCollectionPathUpdated(m_currentCollectionPath);
}

void Repository::removeItem(QString itemName)
{
    m_currentCollection.removeItem(itemName);

    SaveToFileInteractor saveToFile;
    CollectionToStringInteractor convertToString;
    saveToFile.execute(m_currentCollectionPath, convertToString.execute(m_currentCollection));

    emit currentCollectionPathUpdated(m_currentCollectionPath);
}

QString Repository::getRequestContent(QString itemName)
{
    return m_currentCollection.getRequestContent(itemName);
}
