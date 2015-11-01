#include "listener.h"
#include <QtNetwork/QHostAddress>
#include <QTcpSocket>
#include <iostream>
#include <QtWebSockets/QWebSocketCorsAuthenticator>

Listener::Listener() : webServer_( new QWebSocketServer(QStringLiteral("Echo Server"),
                                                  QWebSocketServer::NonSecureMode))
{
    //QWebSocketCorsAuthenticator* qwsa = new QWebSocketCorsAuthenticator("localhost:8080");
    //qwsa->setAllowed(true);
    //server = new QTcpServer();
//    server->listen(QHostAddress::AnyIPv4, 8080);
    //server->listen(QHostAddress::LocalHost, 8080);
    webServer_->listen(QHostAddress::LocalHost, 8080);

    //connect(server, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
    connect(webServer_, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
    connect(webServer_, SIGNAL(closed()), this, SLOT(onClosed()));
    std::cout << webServer_->isListening()  << " " << QHostAddress::LocalHost << std::endl;
}

void Listener::onClosed()
{
    std::cout << "CLOSED" << std::endl;
}

Listener::~Listener()
{

}

void Listener::incomingConnection()
{
    std::cout << "INCOMING CONNECTION" << std::endl;
    webConnection_ = webServer_->nextPendingConnection();
    //clientConnection_ = server->nextPendingConnection();
    //QByteArray data;
    //data.append("Hello\n");
    connect(webConnection_, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessageReceived(QString)) );
    connect(webConnection_, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessageReceived(QByteArray)) );


//    clientConnection->close();
}

void Listener::onBinaryMessageReceived(QByteArray message)
{
    qDebug("bin mess");
    emit(nextPicture());
}



void Listener::onTextMessageReceived(QString message)
{
    qDebug("txt mess");
    qDebug(message.toStdString().c_str());
    emit(nextPicture());
}

void Listener::onReadyRead()
{
    std::cout << "ReadyRead" << std::endl;
    QString command = QString (clientConnection_->readAll());
    std::cout << command.toStdString() << std::endl;

    if( !command.contains("xxxdata=") )
    {
        qDebug("error: no xxxdata=");
        return;
    }
    size_t pos = command.toStdString().find("xxxdata=") + 8;
    std::string data = command.toStdString().substr(pos);
    qDebug(data.c_str());
    if( data == "next" )
    {
        emit(nextPicture());
        std::cout << "right!" << std::endl;
    }
    else
    {
        std::cout << "wrong " << command.toStdString() << std::endl;
    }

    QByteArray answ;
    answ.append("Hello\n");
    clientConnection_->write(answ);
    clientConnection_->close();
}


