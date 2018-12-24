#include "collection_from_string_interactor.h"

CollectionFromStringInteractor::CollectionFromStringInteractor()
{

}

Collection CollectionFromStringInteractor::execute(QString s)
{
    bool ok;
    QtJson::JsonObject result = QtJson::parse(s, ok).toMap();
    if(ok)
    {
        Collection collection("");
        collection.setName(result["collection_name"].toString());
        QtJson::JsonArray items = result["collection_items"].toList();
        for(auto item : items)
        {
            QtJson::JsonObject itemObject = item.toMap();
            QString title = itemObject["title"].toString();
            QString content = itemObject["content"].toString();

            collection.addItem(CollectionItem(title, content));
        }
        return collection;
    }
    else
    {
        throw std::invalid_argument("invalid collection file");
    }
}
