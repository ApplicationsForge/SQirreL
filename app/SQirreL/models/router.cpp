#include "router.h"

Router::Router(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this))
{
    setupConnections();
}

Router::~Router()
{
    resetConnections();
}

Router &Router::getInstance()
{
    static QScopedPointer<Router> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new Router() );
    }
    return *m_instance;
}

Repository *Router::getRepository()
{
    return m_repository.data();
}

void Router::setupConnections()
{

}

void Router::resetConnections()
{

}

void Router::setDatabase(QString path, Repository::DB_TYPE type)
{
    m_repository->setDatabasePath(path);
    m_repository->setDatabaseType(type);
}

QList<QSqlRecord> Router::executeSQL(QString request)
{
    QList<QSqlRecord> result;
    switch (m_repository->m_currentAdapter) {
    case Repository::DB_TYPE::SQLite:
    {
        try
        {
            SQLiteAdapter adapter(this);
            result = adapter.executeSQL(m_repository->m_databasePath, request);
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

