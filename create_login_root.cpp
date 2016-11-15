#include "create_login_root.h"
#include "ui_create_login_root.h"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCloseEvent>
#include <QString>
#include <QMessageBox>
#include <QDebug>

Create_Login_root::Create_Login_root(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Login_root)
{
    ui->setupUi(this);
}

Create_Login_root::~Create_Login_root()
{
    delete ui;
}

void Create_Login_root::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Cancel setup",
                                                                    tr("Closing this window will cancel the setup. Continue?"),
                                                                    QMessageBox::Yes |
                                                                    QMessageBox::No);

    if(resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}

void Create_Login_root::checkInput() {
    QString username;
    QString password;
    QString passwordtc;

    if(ui->usernameLineEdit->text().isEmpty()) {
        username = ui->usernameLineEdit->placeholderText();
    } else {
        username = ui->usernameLineEdit->text();
    }

    if(ui->passwordLineEdit->text().isEmpty() || ui->confirmPasswordLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Enter password", tr("Please enter both passwords to continue"), QMessageBox::Ok);
        return;
    }

    password = ui->passwordLineEdit->text();
    passwordtc = ui->confirmPasswordLineEdit->text();

    if(password != passwordtc) {
        QMessageBox::warning(this, "Error", tr("The passwords you have entered do not match. Please try again"), QMessageBox::Ok);
        return;
    }

    // username VARCHAR(200), pass VARCHAR(200), ugroup VARCHAR(200), perms VARCHAR(10)

    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);
    query.exec("INSERT INTO jotel_users VALUES ('" + username + "', '" + password + "', 'admin', '0') ");
    QMessageBox::StandardButton done = QMessageBox::information(this, tr("Admin account created"), "Successfully created"
                                                                                                   " the admin account", QMessageBox::Ok);

    if(done == QMessageBox::Ok) {
        this->destroy();
    }


    // Else they've entered
}

void Create_Login_root::accept() {
    checkInput();
}

void Create_Login_root::reject() {

}
