#include "open_collection_interactor.h"

OpenCollectionInteractor::OpenCollectionInteractor(QObject *parent) :
    QObject(parent),
    m_readerThread(new QThread(this))
{
    m_readerThread->setObjectName("OpenSQLCollectionThread");
}

OpenCollectionInteractor::~OpenCollectionInteractor()
{
    if(m_readerThread->isRunning())
    {
        m_readerThread->quit();
        m_readerThread->wait();
    }
    delete m_readerThread;
}

void OpenCollectionInteractor::execute(QString filePath)
{
    FileReader* reader = new FileReader();
    reader->moveToThread(m_readerThread);
    connect(m_readerThread, SIGNAL(finished()), reader, SLOT(deleteLater()));
    connect(reader, SIGNAL(successfullRead(QString)), this, SLOT(onFileLoaded(QString)));

    QProgressDialog* progressDialog = new QProgressDialog("Opening file. Please wait", "", 0, 100);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setFixedSize(progressDialog->sizeHint());
    progressDialog->setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");

    connect(m_readerThread, SIGNAL(started()), progressDialog, SLOT(show()));
    connect(m_readerThread, SIGNAL(finished()), progressDialog, SLOT(deleteLater()));
    connect(reader, SIGNAL(loading(int)), progressDialog, SLOT(setValue(int)));

    m_readerThread->start();
    reader->readFileInfo(filePath);
}

void OpenCollectionInteractor::onFileLoaded(QString content)
{
    m_readerThread->quit();
    m_readerThread->wait();
    emit fileLoaded(content);
}
