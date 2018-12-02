#ifndef SQL_SYNTAX_HIGHLIGHTER_H
#define SQL_SYNTAX_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QString>
#include <QRegExp>
#include <vector>


class SqlSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    SqlSyntaxHighlighter(QObject *parent);
    void highlightBlock(const QString &text);
    void setPattern();
private:
    QList<QString> keywordPattern;
    QList<QString> argumentsPattern;
    QList<QString> commentsPattern;

    void setHighlightColor(const QString &text, QList<QString> pattern, const QBrush &brush);

};

#endif // SQL_SYNTAX_HIGHLIGHTER_H
