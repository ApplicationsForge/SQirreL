#ifndef COLLECTION_FROM_STRING_INTERACTOR_H
#define COLLECTION_FROM_STRING_INTERACTOR_H

#include <QString>

#include "libs/json_parser/json.h"
#include "models/types/collection.h"

class CollectionFromStringInteractor
{
public:
    CollectionFromStringInteractor();

    Collection execute(QString s);
};

#endif // COLLECTION_FROM_STRING_INTERACTOR_H
