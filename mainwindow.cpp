#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCursor>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <iostream>
#include <QKeyEvent>
#include "listener.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setGeometry(0,0,0,0);
    setPicture("/home/oleksii/Pictures/waterfall.jpg");
//    ui->label->setScaledContents(true);
    //ui->graphicsView->show();
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    getAllImages();
}


void MainWindow::setPicture(std::string path)
{
    std::cout << "lal" << std::endl;
    QPixmap pm(path.c_str());
//    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pm);
//    QGraphicsScene* scene = new QGraphicsScene();
//    ui->graphicsView->setScene(scene);
//    scene->addItem(item);
//    ui->graphicsView->resize(this->size());
    std::cout << "trying to set " << path << std::endl;
    QFileInfo file(path.c_str());
    if( !file.exists() )
    {
        std::cout << "file dos not exists" << std::endl;
        return;
    }
    ui->label->setPixmap(pm);

    //ui->label->setAlignment( Qt::AlignLeft );

    ui->label->resize(/*this->size()*/ pm.size());
    //    ui->label->set
//    ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


}

void MainWindow::getAllImages()
{
    QDir baseDir(basePath_);
    imagePathses_ = baseDir.entryList(QDir::NoDotAndDotDot | QDir::Files);

    //    auto i = 9;
    std::cout << imagePathses_.size() <<std::endl;
    for(auto i: imagePathses_ )
        qDebug( QString(i).toStdString().c_str() );

    currentPic = imagePathses_.end();
}

void MainWindow::loadNext()
{
    if( currentPic == imagePathses_.end() || currentPic == --imagePathses_.end() )
    {
        std::cout << "test1 size = " << imagePathses_.size() << std::endl;
        currentPic = imagePathses_.begin();
    }
    else
    {
        ++currentPic;
    }

    std::cout << "test2" << std::endl;
    setPicture( (basePath_ + "/" + *currentPic).toStdString());
    std::cout << "test3" << std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
   // std::cout << event->key() <<std::endl;
    if( event->key() == Qt::Key_Right)
    {
        std::cout << "lol" << std::endl;
        loadNext();
    }
}

void MainWindow::startServer()
{
    Listener_ = new Listener();
    connect( Listener_, SIGNAL(nextPicture()), this, SLOT(onNextPicture()) );
}

void MainWindow::onNextPicture()
{
    loadNext();
}

MainWindow::~MainWindow()
{
    delete ui;
}

