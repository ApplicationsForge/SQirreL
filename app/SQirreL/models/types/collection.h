#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>

#include "models/types/collection_item.h"

class Collection
{
public:
    Collection(QString name);

    QString name() const;
    void setName(const QString &name);

    QList<CollectionItem> items() const;
    void setItems(const QList<CollectionItem> &items);

private:
    QString m_name;
    QList<CollectionItem> m_items;
};

#endif // COLLECTION_H
