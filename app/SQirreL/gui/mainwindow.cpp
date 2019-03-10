#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_hightlighter(new SqlSyntaxHighlighter(this))
{
    ui->setupUi(this);

    auto toolbar = ui->mainToolBar;
    toolbar->addAction(ui->actionTemplates);

    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("Ready"));

    m_hightlighter->setDocument(ui->requestTextEdit->document());
    m_hightlighter->setPattern();

    //Router& router = Router::getInstance();
    //ui->label->setText(router.getRepository()->helloString());

    this->showMaximized();

    this->setupConnections();

    this->hideWidgets();
}

MainWindow::~MainWindow()
{
    this->resetConnections();
    delete ui;
}

void MainWindow::setupConnections()
{
    Router& router = Router::getInstance();
    QObject::connect(&router, SIGNAL(currentCollectionUpdated(Collection)), this, SLOT(onRouter_CurrentCollectionUpdated(Collection)));
}

void MainWindow::resetConnections()
{
    Router& router = Router::getInstance();
    QObject::disconnect(&router, SIGNAL(currentCollectionUpdated(Collection)), this, SLOT(onRouter_CurrentCollectionUpdated(Collection)));
}

void MainWindow::hideWidgets()
{
    ui->mainToolBar->hide();
    ui->saveToolButton->hide();
    ui->templatesDockWidget->hide();
}

void MainWindow::onRouter_CurrentCollectionUpdated(Collection collection)
{
    ui->collectionItemsListWidget->clear();
    ui->collectionNameLabel->setText(collection.name());

    QList<CollectionItem> items = collection.items();

    for(auto item : items)
    {
        ui->collectionItemsListWidget->addItem(item.requestName());
    }
}

void MainWindow::on_actionTemplates_triggered()
{
    if(ui->templatesDockWidget->isVisible())
    {
        ui->templatesDockWidget->hide();
    }
    else
    {
        ui->templatesDockWidget->show();
    }
}

void MainWindow::on_runToolButton_clicked()
{
    ui->responseTableWidget->clear();
    ui->responseTableWidget->setColumnCount(0);
    ui->responseTableWidget->setRowCount(0);

    Router& router = Router::getInstance();
    QString request = ui->requestTextEdit->toPlainText();
    QList<QSqlRecord> response = router.executeSQL(request);

    if(response.isEmpty())
    {
        return;
    }

    ui->responseTableWidget->setRowCount(response.length());
    QSqlRecord firstRecord = response.first();
    ui->responseTableWidget->setColumnCount(firstRecord.count());
    for(int columnIndex = 0; columnIndex < firstRecord.count(); columnIndex++)
    {
        ui->responseTableWidget->setHorizontalHeaderItem(columnIndex, new QTableWidgetItem(firstRecord.fieldName(columnIndex)));
    }


    int currentRow = 0;
    for(auto record : response)
    {
        for(int columnIndex = 0; columnIndex < record.count(); columnIndex++)
        {
            ui->responseTableWidget->setItem(currentRow, columnIndex, new QTableWidgetItem(record.value(columnIndex).toString()));
        }
        currentRow++;
    }


    ui->dbLineEdit->setText(router.getRepository()->getDBPath());

    //SELECT * FROM Hen
}

void MainWindow::on_clearToolButton_clicked()
{
    ui->requestTextEdit->clear();
}

void MainWindow::on_openLocalDatabaseToolButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "*.db");
    Router& router = Router::getInstance();
    router.setDatabase(path, Repository::DB_TYPE::SQLite);
    ui->dbLineEdit->setText(router.getRepository()->getDBPath());
}

void MainWindow::on_openTemplateCollectionToolButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "*.json");
    if(path.isEmpty())
    {
        return;
    }


    Router& router = Router::getInstance();
    router.getRepository()->setCurrentCollectionPath(path);
}

void MainWindow::on_saveToolButton_clicked()
{
    /*QString content = ui->requestTextEdit->toPlainText();

    Router& router = Router::getInstance();
    router.getRepository()->addItem(CollectionItem("test", content));*/
}

void MainWindow::on_collectionItemsListWidget_itemClicked(QListWidgetItem *item)
{
    QString requestTitle = item->text();

    Router& router = Router::getInstance();
    QString requestContent = router.getRepository()->getRequestContent(requestTitle);

    ui-> requestTextEdit->setPlainText(requestContent);
}
