#ifndef LISTENER_H
#define LISTENER_H

#include <QtNetwork/QTcpServer>
#include <QWebSocketServer>
#include <QWebSocket>

class Listener : public QObject
{
    Q_OBJECT
public:
    Listener();
    virtual ~Listener();
signals:
    void nextPicture();

public slots:
    void incomingConnection();
    void onReadyRead();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray message);
    void onClosed();
private:
    QTcpServer* server;
    QTcpSocket* clientConnection_;
    QWebSocketServer* webServer_;
    QWebSocket* webConnection_;
};

#endif // LISTENER_H
