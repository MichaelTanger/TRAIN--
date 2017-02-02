#ifndef USERPAGE_H
#define USERPAGE_H

#include <QDialog>
#include "User.h"
#include <QButtonGroup>

namespace Ui {
class userpage;
}

class userpage : public QDialog
{
    Q_OBJECT

public:
    explicit userpage(QString username, QWidget *parent = 0);
    ~userpage();

private slots:
    void pushButtonEdit_clicked();

    void pushButtonEdit_ok_clicked();

    void pushButton_change_clicked();

private:
    Ui::userpage *ui;
    QString username;
    Passenger *aPassenger;
    QButtonGroup *btnGroupSex;
};

#endif // USERPAGE_H
