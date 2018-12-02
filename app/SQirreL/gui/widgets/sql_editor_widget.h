#ifndef SQL_EDITOR_WIDGET_H
#define SQL_EDITOR_WIDGET_H

#include <QObject>
#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

class SqlEditorWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    SqlEditorWidget(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
public:
    ~LineNumberArea() override;

    LineNumberArea(SqlEditorWidget *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    SqlEditorWidget *codeEditor;
};

#endif // SQL_EDITOR_WIDGET_H
