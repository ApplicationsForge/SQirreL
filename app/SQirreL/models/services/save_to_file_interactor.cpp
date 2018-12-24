#include "save_to_file_interactor.h"

SaveToFileInteractor::SaveToFileInteractor()
{

}

void SaveToFileInteractor::execute(QString filePath, QString fileContent)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadWrite))
    {
        throw std::runtime_error("file is not exist");
    }

    QTextStream stream( &file );
    stream << fileContent << endl;
}
