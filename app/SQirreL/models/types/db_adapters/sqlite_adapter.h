#ifndef SQLITE_ADAPTER_H
#define SQLITE_ADAPTER_H

#include <QObject>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMessageBox>

class SQLiteAdapter : public QObject
{
    Q_OBJECT
public:
    explicit SQLiteAdapter(QObject *parent = nullptr);
    ~SQLiteAdapter();

    bool open(QString path);
    void close();
    QSqlQuery runSQL(QString request);

    QString dbLocalPath() const;

private:
    QSqlDatabase m_db;
    QString m_dbLocalPath;

signals:

public slots:
};

#endif // SQLITE_ADAPTER_H
