#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    bool is_blank();

private slots:
    void pushButton_can_clicked();
    void pushButton_reg_clicked();

private:
    Ui::Register *ui;
    QButtonGroup *btnGroupSex;
};

#endif // REGISTER_H
