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
    this, SLOT(allPeopleSlot(QNetworkReply*)));
    allPeopleReply = allPeopleManager->get(request);
}

void MainWindow::on_btnGetOnePerson_clicked()
{
    QString id=ui->lineEdit->text();
    if(id==""){
        ui->label->setText("Annan ID");
    }
    else{
        QString site_url="http://localhost:3000/example/oneperson/"+id;
        QString credentials="ATM123:pass123";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
        onePersonManager = new QNetworkAccessManager(this);
        connect(onePersonManager, SIGNAL(finished (QNetworkReply*)),
        this, SLOT(onePersonSlot(QNetworkReply*)));
        onePersonReply = onePersonManager->get(request);
    }

}

void MainWindow::on_btnGetFullName_clicked()
{
    QString id=ui->lineEdit->text();
    QString site_url="http://localhost:3000/example/fullname/"+id;
    QString credentials="ATM123:pass123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    fullNameManager = new QNetworkAccessManager(this);
    connect(fullNameManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(fullNameSlot(QNetworkReply*)));
    fullNameReply = fullNameManager->get(request);
}

void MainWindow::allPeopleSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0 || response_data.compare("")==0){
        ui->label->setText("Virhe tietokantayhteydess??");
    }
    else{
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();
        QString people;
            foreach (const QJsonValue &value, json_array)
            {
            QJsonObject json_obj = value.toObject();
            people+=QString::number(json_obj["id_person"].toInt())      +"."+json_obj["fname"].toString()+
            " " +json_obj["lname"].toString()+": "+(QString::number(json_obj["money"].toDouble()))+"\r\n";
            }
    ui->label->setText(people);
        }
    allPeopleReply->deleteLater();
    reply->deleteLater();
    allPeopleManager->deleteLater();
}

void MainWindow::onePersonSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->label->setText("Virhe tietokantayhteydess??");
    }
    else if(response_data.compare("")==0)
    {
        ui->label->setText("Henkil???? ei l??ytynyt");
    }
    else
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_obj=json_doc.object();
        QString person=QString::number((json_obj["id_person"].toInt()))+". "+json_obj["fname"].toString()+" "+json_obj["lname"].toString()+": "+(QString::number(json_obj["money"].toDouble()))+"\r\n";
        ui->label->setText(person);
    }
    onePersonReply->deleteLater();
    reply->deleteLater();
    onePersonManager->deleteLater();
}

void MainWindow::fullNameSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->label->setText("Virhe tietokantayhteydess??");
    }
    else if(response_data.compare("")==0)
    {
        ui->label->setText("Henkil???? ei l??ytynyt");
    }
    else
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_obj=json_doc.object();
        QString person=json_obj["fullname"].toString()+"\r\n";
        ui->label->setText(person);
    }

    fullNameReply->deleteLater();
    reply->deleteLater();
    fullNameManager->deleteLater();
}

void MainWindow::raiseSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->label->setText("Virhe tietokantayhteydess??");
    }
    else if(response_data.compare("0")==0)
    {
        ui->label->setText("Nosto ei onnistu");
    }
    else
    {
        ui->label->setText("Nosto onnistui!");
    }
    raiseReply->deleteLater();
    reply->deleteLater();
    raiseManager->deleteLater();
}

void MainWindow::on_clear_clicked()
{
    ui->label->setText(" ");
    ui->lineEdit->setText(" ");
}

void MainWindow::on_btnRaise_clicked()
{
    QString id=ui->lineEditRaiseID->text();
    QString amount=ui->lineEditRaiseAmount->text();
    QJsonObject json_obj;
    json_obj.insert("id",id);
    json_obj.insert("amount",amount);
    QString site_url="http://localhost:3000/person/money_action";
    QString credentials="ATM123:pass123";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() ); raiseManager = new
    QNetworkAccessManager(this);
    raiseManager = new QNetworkAccessManager(this);
    connect(raiseManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(raiseSlot(QNetworkReply*)));
    raiseReply = raiseManager->post(request, QJsonDocument(json_obj).toJson());
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->btnGetFullName->setEnabled(true);
}
