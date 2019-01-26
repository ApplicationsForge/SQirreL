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
        "CREATE",
        "DROP",
        "ALTER",
        "SELECT",
        "INSERT",
        "UPDATE",
        "DELETE",
        "COMMIT",
        "ROLLBACK"
        "INSERT",
        "INTO"
        "SET",
        "GRANT",
        "REVOKE",
        ";",
        "DISTINCT",
        "FROM",
        "JOIN",
        "ON",
        "WHERE",
        "GROUP BY",
        "HAVING",
        "ORDER BY",
        "LEFT",
        "RIGHT",
        "FULL",
        "CROSS",
        "AND",
        "OR",
        "IS",
        "IN",
        "NOT",
        "BETWEEN",
        "LIKE",
        "ASK",
        "DESC",
        "COUNT",
        "MAX",
        "MIN",
        "ADD"
    };

    argumentsPattern =
    {
        "DATABASE",
        "TABLE",
        "DOMAIN",
        "INDEX",
        "VIEW",
        "TRANSACTION",
        "NULL",
        "PRIMARY KEY",
        "FOREIGN KEY",
        "REFERENCES",
        "DEFAULT",
        "COLUMN",
        "CONSTRAINT"
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
