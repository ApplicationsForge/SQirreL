#include "collection.h"

Collection::Collection(QString name) :
    m_name(name),
    m_items(QList<CollectionItem>())
{

}

QString Collection::name() const
{
    return m_name;
}

void Collection::setName(const QString &name)
{
    m_name = name;
}

QList<CollectionItem> Collection::items() const
{
    return m_items;
}

void Collection::setItems(const QList<CollectionItem> &items)
{
    m_items = items;
}

void Collection::addItem(CollectionItem item)
{
    m_items.append(item);
}

void Collection::removeItem(QString itemName)
{
    QList<CollectionItem> tmp;
    for(auto item : m_items)
    {
        if(item.requestName() != itemName)
        {
            tmp.append(item);
        }
    }
    this->setItems(tmp);
}

QString Collection::getRequestContent(QString itemName)
{
    QString result = "";
    for(auto item : m_items)
    {
        if(item.requestName() == itemName)
        {
            result = item.requestContent();
            break;
        }
    }
    return result;
}
