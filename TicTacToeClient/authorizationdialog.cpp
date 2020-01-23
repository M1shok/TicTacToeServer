#include "authorizationdialog.h"
#include "ui_authorizationdialog.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}

QString AuthorizationDialog::userLogin() const
{
    return ui->leLogin->text();
}

QString AuthorizationDialog::userPassword() const
{
    return ui->lePassword->text();
}
