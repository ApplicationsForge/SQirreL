#include "collection_to_string_interactor.h"

CollectionToStringInteractor::CollectionToStringInteractor()
{

}

QString CollectionToStringInteractor::execute(Collection collection)
{
    QtJson::JsonObject generalPackage;
    generalPackage["collection_name"] = collection.name();

    QtJson::JsonArray collectionItems;
    for(auto item : collection.items())
    {
        QtJson::JsonObject collectionItem;
        collectionItem["title"] = item.requestName();
        collectionItem["content"] = item.requestContent();
        collectionItems.append(collectionItem);
    }

    generalPackage["collection_items"] = collectionItems;


    return QtJson::serializeStr(generalPackage);
}
