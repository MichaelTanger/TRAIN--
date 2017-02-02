#ifndef CHANGETRAIN_H
#define CHANGETRAIN_H

#include <QDialog>
#include "Train.h"

namespace Ui {
class changetrain;
}

class changetrain : public QDialog
{
    Q_OBJECT

public:
    explicit changetrain(Train train, QWidget *parent = 0);
    ~changetrain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::changetrain *ui;
};

#endif // CHANGETRAIN_H
