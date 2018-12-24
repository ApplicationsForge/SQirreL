#include "collection_item.h"

CollectionItem::CollectionItem(QString name, QString content) :
    m_requestName(name),
    m_requestContent(content)
{

}

QString CollectionItem::requestName() const
{
    return m_requestName;
}

void CollectionItem::setRequestName(const QString &requestName)
{
    m_requestName = requestName;
}

QString CollectionItem::requestContent() const
{
    return m_requestContent;
}

void CollectionItem::setRequestContent(const QString &requestContent)
{
    m_requestContent = requestContent;
}
