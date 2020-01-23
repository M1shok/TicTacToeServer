#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

    QString userLogin() const;
    QString userPassword() const;

private:
    Ui::RegistrationDialog *ui;
};

#endif // REGISTRATIONDIALOG_H
