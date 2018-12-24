#ifndef OPEN_COLLECTION_INTERACTOR_H
#define OPEN_COLLECTION_INTERACTOR_H

#include <QObject>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QProgressDialog>
#include <QTime>
#include <QThread>
#include <QProgressDialog>

#include "models/utils/file_reader.h"

class OpenCollectionInteractor : public QObject
{
    Q_OBJECT
public:
    explicit OpenCollectionInteractor(QObject *parent = nullptr);
    ~OpenCollectionInteractor();

    void execute(QString filePath);

private:
    QThread* m_readerThread;

signals:
    void fileLoaded(QString content);

public slots:
    void onFileLoaded(QString content);
};

#endif // OPEN_COLLECTION_INTERACTOR_H
