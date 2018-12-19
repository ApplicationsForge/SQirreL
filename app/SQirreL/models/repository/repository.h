#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

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

private:
    QString m_helloString = "SQirreL";
    QScopedPointer<SQLiteAdapter> m_sqliteAdapter;

    DB_TYPE m_currentAdapter;

    bool openSQLiteDatabase(QString localPath);
    QSqlQuery getSQLResult(QString request);

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
