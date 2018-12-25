#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QMessageBox>

#include "models/types/collection.h"
#include "models/services/save_to_file_interactor.h"
#include "models/services/collection_to_string_interactor.h"

class Router;

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);
    ~Repository();

    enum DB_TYPE { SQLite };

    QString getDBPath();

    QString getDatabasePath() const;
    void setDatabasePath(const QString &databasePath);
    void setDatabaseType(DB_TYPE type);

    QString getCurrentCollectionPath() const;
    void setCurrentCollectionPath(const QString &currentCollectionPath);

    Collection getCurrentCollection() const;
    void setCurrentCollection(const Collection &currentCollection);

    void addItem(CollectionItem item);
    void removeItem(QString itemName);
    QString getRequestContent(QString itemName);

private:
    DB_TYPE m_currentAdapter;
    QString m_databasePath;

    QString m_currentCollectionPath;
    Collection m_currentCollection;


    friend class Router;

signals:
    void currentCollectionPathUpdated(QString path);

public slots:
};

#endif // REPOSITORY_H
