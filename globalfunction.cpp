#include "globalfunction.h"
#include <QDateTime>

QString getTimestamp() {
    auto time = QDateTime(QDateTime::currentDateTime());
    return time.toString("yyyy-MM-dd hh:mm:ss.zzz");
}

QByteArray dataToHex(const QByteArray &data) {
    QByteArray result = data.toHex().toUpper();

    for (int i = 2; i < result.size(); i += 3)
        result.insert(i, ' ');

    return result;
}

QByteArray dataFromHex(const QString &hex) {
    QByteArray line = hex.toLatin1();
    line.replace(' ', QByteArray());
    auto result = QByteArray::fromHex(line);
    return result;
}
