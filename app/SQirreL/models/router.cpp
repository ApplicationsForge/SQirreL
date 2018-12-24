#include "router.h"

Router::Router(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_openCollection(new OpenCollectionInteractor(this))
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
    QObject::connect(m_repository.data(), SIGNAL(currentCollectionPathUpdated(QString)), this, SLOT(onRepository_CurrentCollectionPathUpdated(QString)));
    QObject::connect(m_openCollection.data(), SIGNAL(fileLoaded(QString)), this, SLOT(onOpenCollectionInteractor_FileLoaded(QString)));
}

void Router::resetConnections()
{
    QObject::disconnect(m_repository.data(), SIGNAL(currentCollectionPathUpdated(QString)), this, SLOT(onRepository_CurrentCollectionPathUpdated(QString)));
    QObject::disconnect(m_openCollection.data(), SIGNAL(fileLoaded(QString)), this, SLOT(onOpenCollectionInteractor_FileLoaded(QString)));
}

void Router::onRepository_CurrentCollectionPathUpdated(QString path)
{
    m_openCollection.data()->execute(path);
}

void Router::onOpenCollectionInteractor_FileLoaded(QString content)
{
    // parse content to collection

    qDebug() << content;

    m_repository.data()->setCurrentCollection(Collection("Mock"));
    emit currentCollectionUpdated(m_repository->getCurrentCollection());
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

