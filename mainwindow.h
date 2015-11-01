#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <listener.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startServer();
protected:
    void keyPressEvent(QKeyEvent* event);

public slots:
    void onNextPicture();

private:
    void getAllImages();
    void loadNext();
    void setPicture(std::string path);
    Ui::MainWindow *ui;
    QStringList imagePathses_;
    QStringList::iterator currentPic = imagePathses_.end();
    QString basePath_ = "/home/oleksii/Pictures/";
    Listener* Listener_;
};

#endif // MAINWINDOW_H
