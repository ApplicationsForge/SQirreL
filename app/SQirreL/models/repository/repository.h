#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QMessageBox>

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

private:
    DB_TYPE m_currentAdapter;
    QString m_databasePath;

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
