#ifndef SAVE_TO_FILE_INTERACTOR_H
#define SAVE_TO_FILE_INTERACTOR_H

#include <QString>
#include <QFile>
#include <QTextStream>

class SaveToFileInteractor
{
public:
    SaveToFileInteractor();

    void execute(QString filePath, QString fileContent);
};

#endif // SAVE_TO_FILE_INTERACTOR_H
