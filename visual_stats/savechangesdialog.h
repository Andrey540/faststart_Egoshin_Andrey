#ifndef SAVECHANGESDIALOG
#define SAVECHANGESDIALOG

#include <QDialog>

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

private slots:
    void onAccepted();

private:
    Ui::SaveChangesDialog *ui;
};

#endif // SAVECHANGESDIALOG


