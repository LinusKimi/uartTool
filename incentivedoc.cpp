#include "incentivedoc.h"

IncentiveDoc::IncentiveDoc()
{

}

bool IncentiveDoc::createCLFile(QString filePath)
{
    //添加xml说明
    QDomDocument doc;
    QDomProcessingInstruction instru;
    instru = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instru);

    QFile _file(filePath);

    if(!_file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return false;

    //输出到文件
    QTextStream out_stream(&_file);
    doc.save(out_stream,4); //缩进4格
    _file.close();

}

bool IncentiveDoc::readCLFile(QList<struct CMDDATA> &data, QString filePath)
{
    QFile _file(filePath);
    if(!_file.open(QFile::ReadOnly))
        return false;

    QDomDocument doc("clFile");

    if(!doc.setContent(&_file))
    {
        _file.close();
        return false;
    }



    return true;
}

bool IncentiveDoc::writeCLFile(const QList<struct CMDDATA> &data, QString filePath)
{
    QFile _file(filePath);
    if(!_file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return false;



    return true;
}

