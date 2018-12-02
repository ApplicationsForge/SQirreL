#include "sql_syntax_highlighter.h"

SqlSyntaxHighlighter::SqlSyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{

}



void SqlSyntaxHighlighter::highlightBlock(const QString &text)
{
    setHighlightColor(text, keywordPattern, Qt::darkMagenta);
    setHighlightColor(text, argumentsPattern, Qt::darkBlue);
    setHighlightColor(text, commentsPattern, Qt::darkGreen);
}

void SqlSyntaxHighlighter::setPattern()
{
    keywordPattern =
    {
        "SELECT",
        "UPDATE",
        "DELETE",
        "INSERT INTO",
        "CREATE DATABASE",
        "ALTER DATABASE",
        "CREATE TABLE",
        "ALTER TABLE",
        "DROP TABLE",
        "CREATE INDEX",
        "DROP INDEX"
    };

    argumentsPattern =
    {
        "FROM",
        "LEFT",
        "RIGHT",
        "JOIN"
    };

    commentsPattern =
    {
        "[(]([^{}]*)[)]"
    };
}

void SqlSyntaxHighlighter::setHighlightColor(const QString &text, QList<QString> pattern, const QBrush &brush)
{
    QTextCharFormat format;

    for(auto i : pattern)
    {
        QRegExp rx(i);
        if(!rx.isValid() || rx.isEmpty() || rx.exactMatch(""))
        {
            setFormat(0, text.length(), format);
            return;
        }
        format.setForeground(brush);
        int index = rx.indexIn(text);
        while(index >= 0)
        {
            int length = rx.matchedLength();
            setFormat(index, length, format);
            index = rx.indexIn(text, index + length);
        }
    }
}
