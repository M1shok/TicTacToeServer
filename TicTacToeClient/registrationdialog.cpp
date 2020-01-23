#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

QString RegistrationDialog::userLogin() const
{
    return ui->leLogin->text();
}

QString RegistrationDialog::userPassword() const
{
    return ui->lePassword->text();
}
