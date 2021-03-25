#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGetAllPeople_clicked()
{
    QString site_url="http://localhost:3000/example/allpeople";
    QString credentials="ATM123:pass123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    allPeopleManager = new QNetworkAccessManager(this);
    connect(allPeopleManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getBookSlot(QNetworkReply*)));
    allPeopleReply = allPeopleManager->get(request);
}

void MainWindow::on_btnGetOnePerson_clicked()
{

}

void MainWindow::on_btnGetFullName_clicked()
{

}

void MainWindow::allPeopleSlot(QNetworkReply *reply)
{

}
