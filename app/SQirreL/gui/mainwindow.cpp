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
    toolbar->addAction(ui->actionOpenLocalSQLiteDatabase);

    ui->templatesDockWidget->hide();

    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    m_hightlighter->setDocument(ui->requestTextEdit->document());
    m_hightlighter->setPattern();

    //Router& router = Router::getInstance();
    //ui->label->setText(router.getRepository()->helloString());

    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_actionOpenLocalSQLiteDatabase_triggered()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберите файл базы данных", "", "*.db");
    Router& router = Router::getInstance();
    if(router.openDB(path, Repository::DB_TYPE::SQLite))
    {
        ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
        ui->statusBar->showMessage(tr("SQLite local db is connected"));
    }
    else
    {
        ui->statusBar->setStyleSheet("background-color: #333; color: #bb3333");
        ui->statusBar->showMessage(tr("SQLite local db is not connected"));
    }
}

void MainWindow::on_runToolButton_clicked()
{
    Router& router = Router::getInstance();
    QString request = ui->requestTextEdit->toPlainText();
    QSqlQuery response = router.runSQL(request);

    if(response.lastError().text() != " ")
    {
        qDebug() << response.lastError().text();
    }
    while (response.next())
    {
        qDebug() << response.value(0).toString();
    }

    //SELECT * FROM Hen
}

void MainWindow::on_clearToolButton_clicked()
{
    ui->requestTextEdit->clear();
}
