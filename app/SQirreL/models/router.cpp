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

bool Router::openDB(QString path, Repository::DB_TYPE type)
{
    bool result = false;
    switch (type) {
    case Repository::DB_TYPE::SQLite:
    {
        result = m_repository->openSQLiteDatabase(path);
        break;
    }
    default:
    {
        break;
    }
    }
    return result;
}

QSqlQuery Router::runSQL(QString request)
{
    return m_repository->getSQLResult(request);
}

