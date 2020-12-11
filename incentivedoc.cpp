#include "incentivedoc.h"

IncentiveDoc::IncentiveDoc()
{

}

bool IncentiveDoc::readCLFile(QList<struct CMDDATA> &data, QString filePath)
{
    QFile _file(filePath);
    if(!_file.open(QFile::ReadOnly))
        return true;


}

bool IncentiveDoc::writeCLFile(const QList<struct CMDDATA> &data, QString filePath)
{
    QFile _file(filePath);
    if(!_file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return false;

    return true;
}

