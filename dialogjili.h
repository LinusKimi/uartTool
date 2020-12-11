#ifndef DIALOGJILI_H
#define DIALOGJILI_H

#include <QDialog>

namespace Ui {
class DialogJili;
}

typedef struct
{
    // 是否 无限循环
    bool infiniteStyle;

    // 有限激励 次数
    int64_t finitudeCnt;
}JILIType;

class DialogJili : public QDialog
{
    Q_OBJECT
signals:
    void sendData(JILIType);

public:
    explicit DialogJili(QWidget *parent = nullptr);
    ~DialogJili();



private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialogJili *ui;
    JILIType _jiliType;
};

#endif // DIALOGJILI_H
