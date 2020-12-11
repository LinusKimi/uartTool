#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H

#include <QString>
#include <QWidget>

extern QString getTimestamp();

extern QByteArray dataToHex(const QByteArray &data);

extern QByteArray dataFromHex(const QString &data);

#endif // GLOBALFUNCTION_H
