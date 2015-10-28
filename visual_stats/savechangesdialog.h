#ifndef SAVECHANGESDIALOG
#define SAVECHANGESDIALOG

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class SaveChangesDialog;
}

class SaveChangesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveChangesDialog(QWidget *parent = 0);
    ~SaveChangesDialog();

signals:
    void doSave(bool needSave);
    void doCancel();

private slots:
    void onAccepted();
    void onClicked(QAbstractButton * button);

private:
    Ui::SaveChangesDialog *ui;
};

#endif // SAVECHANGESDIALOG


