#include "databaseinput.h"
#include "ui_databaseinput.h"
#include "databaseconnection.h"
#include "create_login_root.h"
#include "admin/room_editor.h"
#include "tableverify.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>
#include <QCoreApplication>
#include <QSqlQuery>

#include <QDebug>

DatabaseInput::DatabaseInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseInput)
{
    ui->setupUi(this);
}

void DatabaseInput::closeEvent(QCloseEvent* event) {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Exit",
                                                                    tr("Exit setup?"),
                                                                    QMessageBox::Cancel |
                                                                    QMessageBox::Ok);

    if(resBtn != QMessageBox::Ok) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}

// Check all the inputs are okay here
void DatabaseInput::checkInput() {
    // Check IP box
    QString ts_ip;
    QString ts_dbname;
    QString ts_user;
    QString ts_password;

    if(ui->databaseIPLineEdit->text().isEmpty()) {
        ts_ip = ui->databaseIPLineEdit->placeholderText();
    } else {
        ts_ip = ui->databaseIPLineEdit->text();
    }

    if(ui->databaseNameLineEdit->text().isEmpty()) {
        ts_dbname = ui->databaseNameLineEdit->placeholderText();
    } else {
        ts_dbname = ui->databaseNameLineEdit->text();
    }

    if(ui->databaseUserLineEdit->text().isEmpty()) {
        ts_user = ui->databaseUserLineEdit->placeholderText();
    } else {
        ts_user = ui->databaseUserLineEdit->text();
    }

    QRegExp re("\\d*");
    if(!re.exactMatch(ui->portLineEdit->text())) {
        QMessageBox::warning( this, "Invalid port", tr("Please enter a valid port number"));
        return;
    }

    // Goes last, decides to carry on
    if(ui->databasePasswordLineEdit->text().isEmpty()) {
        QMessageBox::StandardButton nopasswordbox = QMessageBox::question(this, "No password", tr(
                                                                             "Do you want to continue without entering a pasword?"),
                                                                         QMessageBox::Yes | QMessageBox::No);


        if(nopasswordbox == QMessageBox::Yes) {
            ts_password = "";
        } else {
            return;
        }
    } else {
        ts_password = ui->databasePasswordLineEdit->text();
    }

    DatabaseConnection* dbconn = new DatabaseConnection();
    if(dbconn->isConnectableDatabase(ts_ip, ts_dbname, ts_user, ts_password, ui->portLineEdit->text().toInt())) {
        greyOut();
        QMessageBox::StandardButton info =QMessageBox::information(this, "Connected",
                                                                   tr("Connected successfully to the database"), QMessageBox::Ok);

        dbconn->openConnection(ts_ip, ts_dbname, ts_user, ts_password, ui->portLineEdit->text().toInt());

        TableVerify* tablev = new TableVerify();
        tablev->checkTables();

        QSqlDatabase db = QSqlDatabase::database();

        if(info == QMessageBox::Ok) {

            QSqlQuery query(db);
            query.exec("SELECT username FROM jotel_users WHERE username = 'admin'");

            if(!query.next()) { // If nothing is found in the database
                QMessageBox::StandardButton adminsetup = QMessageBox::question(this, "Enter admin setup",
                                                                               tr("No admin account found! Setup admin account now?"), QMessageBox::Yes | QMessageBox::No);
                if(adminsetup == QMessageBox::Yes) {
                    dbconn->openConnection(ts_ip, ts_dbname, ts_user, ts_password, ui->portLineEdit->text().toInt());
                    Create_Login_root* clr = new Create_Login_root();
                    this->destroy();
                    clr->setModal(true);
                    clr->show();
                } else {
                    QMessageBox::StandardButton nadmin = QMessageBox::warning(this, "Error", tr("No admin account found. Open Jotel again to set the admin account up"), QMessageBox::Ok);

                    if(nadmin == QMessageBox::Ok) {
                        QApplication::quit();
                    }
                }
            } else {
                /*
                 *
                 * I mean we really don't need this here because if there's no account
                 * and you're forced to make an admin account, then how the hell can you
                 * get to this point.
                 *
                 * Ah well, consumers do. Programmers do this thing called "Retard proofing"
                 *
                 */

                bool adexists = false;

                while(query.next()) {
                    if(query.value(0).toString() == "admin") {
                        adexists = true;
                        break;
                    }
                }

                if(!adexists) {
                    qDebug() << "Fuck not in here oops";
                }

                // Admin account found. Logging in here
            }
        }
    } else {
        QMessageBox::warning(this, "Unable to connect", tr("Unable to connect you to the database. Please try again"), QMessageBox::Ok);
        greyIn();
    }
}

// void checkValid();

void DatabaseInput::greyOut() {
    ui->databaseIPLineEdit->setEnabled(false);
    ui->databaseNameLineEdit->setEnabled(false);
    ui->databasePasswordLineEdit->setEnabled(false);
    ui->databaseUserLineEdit->setEnabled(false);
    ui->portLineEdit->setEnabled(false);
}

void DatabaseInput::greyIn() {
    ui->databaseIPLineEdit->setEnabled(true);
    ui->databaseNameLineEdit->setEnabled(true);
    ui->databasePasswordLineEdit->setEnabled(true);
    ui->databaseUserLineEdit->setEnabled(true);
    ui->portLineEdit->setEnabled(true);
}


void DatabaseInput::accept() {
    checkInput();
}

DatabaseInput::~DatabaseInput()
{
    delete ui;
}
