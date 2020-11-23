#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setMinimumSize(900,800);

    width = 710;
    height = 600;
    im = QImage(width, height, QImage::Format_RGB32);
    im.fill(0xFFFFFF);

    dodaj = new QPushButton("dodaj", this);
    dodaj->setGeometry(720, 20, 175, 40);
    dodaj->setText("Dodaj punkt kontrolny");

    usun = new QPushButton("usun", this);
    usun->setGeometry(720, 70, 175, 40);
    usun->setText("Usuń punkt kontrolny");

    przesun = new QPushButton("przesun", this);
    przesun->setGeometry(720, 120, 175, 40);
    przesun->setText("Przesuń punkt kontrolny");

    dodaj->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    usun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    przesun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));

    r = 0; g = 0; b = 0;

    connect(dodaj, SIGNAL(pressed()), this, SLOT(dodajChanged()));
    connect(usun, SIGNAL(pressed()), this, SLOT(usunChanged()));
    connect(przesun, SIGNAL(pressed()), this, SLOT(przesunChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 0, im);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        p.x = e -> x();
        p.y = e -> y();
        if(rysuj == 1){
            moj.push_back(p);
            drawControlPoint();
        }
    }
    if(moj.size()>3 /*&& moj.size()%3 == 1*/ && rysuj == 1){
        drawBspline();
    }
    if(usun_zm == 1){
        usuwanie();
        qDebug("%d", moj.size());
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        q.x = e -> x();
            q.y = e -> y();
            if(przesun_zm == 1){
            //qDebug("%d %d", p.x, p.y);
            przesuwanie();
            }
    }
}


void MainWindow::dodajChanged()
{
    ld++;
    if(ld%2 == 1){
    usun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    przesun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    dodaj->setStyleSheet(QString::fromUtf8("background-color: rgb(189,236,182);"));
    //lu++;
    //lp++;
    lu = 0;
    lp = 0;
    rysuj = 1;
    usun_zm = 0;
    przesun_zm = 0;
    }
    else {dodaj->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
        //lu--;
        //lp--;
        rysuj = 0;
        usun_zm = 0;
        przesun_zm = 0;

    }
}
void MainWindow::usunChanged()
{
    lu++;
    if(lu%2 == 1){
    usun->setStyleSheet(QString::fromUtf8("background-color: rgb(189,236,182);"));
    przesun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    dodaj->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    //ld++;
    //lp++;
    ld = 0;
    lp = 0;
     rysuj = 0;
     usun_zm = 1;
     przesun_zm = 0;
    }
    else {usun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    //lp--;
    //ld--;
        rysuj = 0;
        usun_zm = 0;
        przesun_zm = 0;

    }
}

void MainWindow::przesunChanged()
{
    lp++;
    if(lp%2 == 1){
    usun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    przesun->setStyleSheet(QString::fromUtf8("background-color: rgb(189,236,182);"));
    dodaj->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    //ld++;
    //lu++;
    lu = 0;
    ld = 0;
     rysuj = 0;
     usun_zm = 0;
     przesun_zm = 1;
    }
    else {przesun->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
    //lu--;
    //ld--;
        rysuj = 0;
        usun_zm = 0;
        przesun_zm = 0;
    }
}

void MainWindow::usuwanie()
{
    if(usun_zm == 1){
        //for(it=moj.begin(); it!=moj.end(); it++){
        for(uint i =0; i<moj.size(); i++){
            if(abs(moj[i].x-p.x)<10 && abs(moj[i].y - p.y)<10){
            qDebug("%d", moj.size());
                moj.erase(moj.begin()+i);
            }
        }
        im.fill(0xFFFFFF);
        pom = 3;
        if(moj.size()>0){
        drawControlPoint();
        int i = 0;
            while(i + 4<= moj.size()){
                i++;
                drawBspline();
            }
        }

    }
    update();
}

void MainWindow::przesuwanie()
{

        for(uint i =0; i<moj.size(); i++){
            if(abs(moj[i].x-p.x)<10 && abs(moj[i].y - p.y)<10){
            qDebug("%d", moj.size());
                moj[i].x = q.x;
                moj[i].y = q.y;
                //moj.erase(moj.begin()+i);
            }
        }
        im.fill(0xFFFFFF);
        pom = 3;
        //if(moj.size()>0){
        drawControlPoint();
        int i = 0;
        //if(moj.size()>1 && moj.size()%3 == 1){
            while(i + 4<= moj.size()){
                i++;
                drawBspline();
            }

   // }
    update();
}


void MainWindow::putPixel(int x, int y)
{
    if(x >= 0 && x < width && y >= 0 && y < height){
        pix = im.scanLine(y);
        pix[x*4] = b;
        pix[x*4 + 1] = g;
        pix[x*4 + 2] = r;
    }
}



void MainWindow::drawBspline(){
    int N = 4;
        uint i = pom;
        double tmp = moj[i-3].x;
        double tmp2 = moj[i-3].y;
        for(int k=0; k<=N; k++){
            double t = (double)k/N;
            p.x = (1.0/6)*(pow(-t,3)+3*pow(t,2)-3*t+1)*moj[i-3].x
                  +(1.0/6)*(3*pow(t,3)-6*pow(t,2)+4)*moj[i-2].x
                  +(1.0/6)*((-3)*pow(t,3)+3*pow(t,2)+3*t+1)*moj[i-1].x
                  +(1.0/6)*pow(t,3)*moj[i].x;
            p.y = (1.0/6)*(pow(-t,3)+3*pow(t,2)-3*t+1)*moj[i-3].y
                  +(1.0/6)*(3*pow(t,3)-6*pow(t,2)+4)*moj[i-2].y
                  +(1.0/6)*((-3)*pow(t,3)+3*pow(t,2)+3*t+1)*moj[i-1].y
                  +(1.0/6)*pow(t,3)*moj[i].y;
            if(k>0) drawSegment(tmp,tmp2,p.x,p.y);
            tmp = p.x;
            tmp2 = p.y;
        }
        pom++;
    update();
}

void MainWindow::swap(int &x, int &y){
    double tmp = x;
    x = y;
    y = tmp;
}

void MainWindow::drawSegment(int x1, int y1, int x2, int y2)
{

    if(x1 == x2 && y1 == y2) putPixel(x1,y1);
    double wsp, wyrazWolny;
    if(abs(x1 - x2) >= abs(y1 - y2)){
        if(x2 < x1){
            swap(x1,x2);
            swap(y1,y2);
        }
        wsp = (y2-y1)/static_cast<double>(x2-x1);
        wyrazWolny = (y1*x2-x1*y2)/static_cast<double>(x2-x1);
        for(int i = x1; i < x2; i++){
            int tmp1 = static_cast<int>(wsp*i+wyrazWolny+0.5);
            putPixel(i,tmp1);
        }
    }
    else{
        if(y2 < y1){
            swap(y1,y2);
            swap(x1,x2);
        }
        wsp = (x2-x1)/static_cast<double>(y2-y1);
        wyrazWolny = (x1*y2-y1*x2)/static_cast<double>(y2-y1);
        for(int i = y1; i < y2; i++){
            int tmp1 = static_cast<int>(wsp*i+wyrazWolny+0.5);
            putPixel(tmp1,i);
        }
    }
}

void MainWindow::drawControlPoint()
{
    for(uint k=0; k<moj.size(); k++){
        for(int i=-5; i<=5; i++){
            if(i == -5 || i == 5){
            for(int j=-5; j<=5; j++){
                putPixel(j+moj[k].x, i+moj[k].y);
            }
            }
            putPixel(-5 + moj[k].x, i+moj[k].y);
            putPixel(5 + moj[k].x, i+moj[k].y);
        }
    }
    update();
}
