#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGetAllPeople_clicked();
    void on_btnGetOnePerson_clicked();
    void on_btnGetFullName_clicked();
    void allPeopleSlot(QNetworkReply *reply);
    void onePersonSlot(QNetworkReply *reply);
    void fullNameSlot(QNetworkReply *reply);
    void raiseSlot(QNetworkReply *reply);

    void on_clear_clicked();

    void on_btnRaise_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *allPeopleManager;
    QNetworkReply *allPeopleReply;

    QNetworkAccessManager *onePersonManager;
    QNetworkReply *onePersonReply;

    QNetworkAccessManager *fullNameManager;
    QNetworkReply *fullNameReply;

    QNetworkAccessManager *raiseManager;
    QNetworkReply *raiseReply;
};
#endif // MAINWINDOW_H
