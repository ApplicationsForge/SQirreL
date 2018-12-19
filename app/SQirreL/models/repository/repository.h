#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QMessageBox>

#include "models/types/db_adapters/sqlite_adapter.h"

class Router;

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);
    ~Repository();

    enum DB_TYPE { SQLite };

    QString helloString() const;
    void setHelloString(const QString &helloString);

    QString getDBPath();

    QString getDatabasePath() const;
    void setDatabasePath(const QString &databasePath);
    void setDatabaseType(DB_TYPE type);

private:
    QString m_helloString = "SQirreL";

    DB_TYPE m_currentAdapter;
    QString m_databasePath;

    QList<QSqlRecord> executeSQL(QString request);

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
