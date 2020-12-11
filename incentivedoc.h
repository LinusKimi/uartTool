#ifndef INCENTIVEDOC_H
#define INCENTIVEDOC_H

#include<QtXml>
#include<QFile>

typedef enum {HexCode, StrindCode, FileCode} CMDDATAFORMAT;

struct
{
    QString         _name;
    CMDDATAFORMAT   _dataType;
    QString         _cmdData;
    uint32_t        _delayTime;
    bool            _active;
}CMDDATA = {"", HexCode, "", 0, false};

class IncentiveDoc
{
private:
    typedef enum{HexCodeType, StringType, FileType} DataType;

public:
    IncentiveDoc();

    bool readCLFile(QList<struct CMDDATA> &, QString);

    bool writeCLFile(const QList<struct CMDDATA> &, QString);

private:
    uint64_t cmdCnt = 0;

};

#endif // INCENTIVEDOC_H
