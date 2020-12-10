#ifndef DIALOGJILI_H
#define DIALOGJILI_H

#include <QDialog>

namespace Ui {
class DialogJili;
}

class DialogJili : public QDialog
{
    Q_OBJECT
signals:
    void sendData(bool, int64_t);

public:
    explicit DialogJili(QWidget *parent = nullptr);
    ~DialogJili();

    // 是否 无限循环
    bool infiniteStyle = true;

    // 有限次数
    int64_t finitudeCnt = 5;

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialogJili *ui;
};

#endif // DIALOGJILI_H
