#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include "User.h"

namespace Ui {
class changepassword;
}

class changepassword : public QDialog
{
    Q_OBJECT

public:
    explicit changepassword(Passenger &p,QWidget *parent = 0);
    ~changepassword();

private slots:
    void pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::changepassword *ui;
    Passenger *pas;
};

#endif // CHANGEPASSWORD_H
