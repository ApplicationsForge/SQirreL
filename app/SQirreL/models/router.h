#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>

#include "models/repository/repository.h"
#include "models/types/db_adapters/sqlite_adapter.h"
#include "models/types/collection.h"
#include "models/services/open_collection_interactor.h"

// Router& router = Router::getInstance();

class Router : public QObject
{
    Q_OBJECT
public:
    static Router& getInstance();
    ~Router();

     Repository* getRepository();

     void setDatabase(QString path, Repository::DB_TYPE type);
     QList<QSqlRecord> executeSQL(QString request);

private:
    explicit Router(QObject *parent = nullptr);

    /// Репозиторий, хранящий текущее состояние
    QScopedPointer<Repository> m_repository;
    QScopedPointer<OpenCollectionInteractor> m_openCollection;

    /**
     * @brief Подключет слоты к сигналам полей класса
     */
    void setupConnections();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetConnections();

signals:
    void currentCollectionUpdated(Collection collection);

public slots:

private slots:
    void onRepository_CurrentCollectionPathUpdated(QString path);
    void onOpenCollectionInteractor_FileLoaded(QString content);
};

#endif // ROUTER_H
