#ifndef COLLECTION_ITEM_H
#define COLLECTION_ITEM_H

#include <QString>

class CollectionItem
{
public:
    CollectionItem(QString name, QString content = "");

    QString requestName() const;
    void setRequestName(const QString &requestName);

    QString requestContent() const;
    void setRequestContent(const QString &requestContent);

private:
    QString m_requestName;
    QString m_requestContent;
};

#endif // COLLECTION_ITEM_H
