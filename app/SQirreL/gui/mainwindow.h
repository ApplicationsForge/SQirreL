#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "models/router.h"
#include "gui/sql_syntax_highlighter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRouter_CurrentCollectionUpdated(Collection collection);

    void on_actionTemplates_triggered();

    void on_runToolButton_clicked();

    void on_clearToolButton_clicked();

    void on_openLocalDatabaseToolButton_clicked();

    void on_openTemplateCollectionToolButton_clicked();

    void on_saveToolButton_clicked();

private:
    Ui::MainWindow *ui;

    /// Подсветки синтаксиса в редакторе SQL
    QScopedPointer<SqlSyntaxHighlighter> m_hightlighter;

    void setupConnections();
    void resetConnections();
};

#endif // MAINWINDOW_H
