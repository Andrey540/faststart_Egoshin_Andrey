#ifndef INSERTROWDIALOG_H
#define INSERTROWDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class InsertRowDialog;
}

class InsertRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertRowDialog(QWidget *parent = 0);
    ~InsertRowDialog();

signals:
    void rowReady(QString text, int value);

private slots:
    void onAccepted();

    void on_editValue_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void on_editName_textChanged(const QString &arg1);

    bool isNameValid(const QString &name);

    bool isValueValid(int value);

    bool isParametersValid(const QString &name, int value);

private:
    Ui::InsertRowDialog *ui;
};

#endif // INSERTROWDIALOG_H
