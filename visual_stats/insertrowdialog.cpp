#include "insertrowdialog.h"
#include "ui_insertrowdialog.h"

InsertRowDialog::InsertRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertRowDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

InsertRowDialog::~InsertRowDialog()
{
    delete ui;
}

void InsertRowDialog::onAccepted()
{
    emit rowReady(ui->editName->text(), ui->editValue->value());
}

void InsertRowDialog::on_editValue_valueChanged(int arg1)
{
    if (!isParametersValid(ui->editName->text(), arg1))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void InsertRowDialog::on_editName_textChanged(const QString &arg1)
{
    if (!isParametersValid(arg1, ui->editValue->value()))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

bool InsertRowDialog::isNameValid(const QString &name)
{
    return name.size() != 0 && name.size() <= 20;
}

bool InsertRowDialog::isValueValid(int value)
{
    return value != 0;
}

bool InsertRowDialog::isParametersValid(const QString &name, int value)
{
    return isNameValid(name) && isValueValid(value);
}


void InsertRowDialog::on_buttonBox_accepted()
{

}
