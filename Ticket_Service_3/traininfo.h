#ifndef TRAININFO_H
#define TRAININFO_H

#include <QDialog>
#include "Train.h"
#include <QDateTime>

namespace Ui {
class traininfo;
}

class traininfo : public QDialog
{
    Q_OBJECT

public:
    explicit traininfo(QWidget *parent = 0);
    ~traininfo();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::traininfo *ui;
    Train *newtrain;
    QDateTime sysTime;
};

#endif // TRAININFO_H
