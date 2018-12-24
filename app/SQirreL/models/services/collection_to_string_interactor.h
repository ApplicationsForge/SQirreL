#ifndef COLLECTION_TO_STRING_INTERACTOR_H
#define COLLECTION_TO_STRING_INTERACTOR_H

#include "libs/json_parser/json.h"

#include "models/types/collection.h"

class CollectionToStringInteractor
{
public:
    CollectionToStringInteractor();

    QString execute(Collection collection);
};

#endif // COLLECTION_TO_STRING_INTERACTOR_H
