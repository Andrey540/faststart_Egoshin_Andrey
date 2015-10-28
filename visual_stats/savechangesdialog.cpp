#include "savechangesdialog.h"
#include "ui_savechangesdialog.h"

SaveChangesDialog::SaveChangesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveChangesDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClicked(QAbstractButton*)));
}

SaveChangesDialog::~SaveChangesDialog()
{
    delete ui;
}

void SaveChangesDialog::onAccepted()
{
    emit doSave(true);
}

void SaveChangesDialog::onClicked(QAbstractButton * button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Cancel)
    {
        emit doCancel();
    }
}
