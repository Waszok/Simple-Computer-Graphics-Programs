#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setMinimumSize(900,800);

    width = 700;
    height = 600;
    im = QImage(width, height, QImage::Format_RGB32);
    im.fill(0xFFFFFF);
    slider = new QSlider(this);
    slider->setGeometry(720,150,16,160);
    slider->setMinimum(0);
    slider->setMaximum(360);
    slider->setSingleStep(1);
    slider->setPageStep(1);

    r = 0; g = 0; b = 0;
    re1 = 0, re2 = 0;
    ge1 = 0; ge2 = 0;
    be1 = 0; be2 = 0;

    //Suwak do obracania elipsy
    connect(slider, SIGNAL(valueChanged(int)) , this, SLOT(obrot(int)));

    //Suwaki do zmiany wartosci r, g, b
    connect(ui->redSlider, SIGNAL(valueChanged(int)) , SLOT(onColorChanged()));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)) , SLOT(onColorChanged()));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)) , SLOT(onColorChanged()));

    //Zmiana kolorow elipsy
    connect(ui->cb1, SIGNAL(clicked(bool)), SLOT(onColorChanged()));
    connect(ui->cb2, SIGNAL(clicked(bool)), SLOT(onColorChanged()));

    //Zatwierdzenie zmian
    connect(ui->accept, SIGNAL(clicked(bool)), this, SLOT(onColorChanged()));
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
        clickNumbers++;
        if(licznik == 0){
            a1 = e -> x();
            a2 = e -> y();
            licznik++;
        }
        else if(licznik == 1){
            b1 = e -> x();
            b2 = e -> y();
            r1 = abs(b1-a1);
            r2 = abs(b2-a2);
            s1 = a1;
            s2 = b2;
            licznik = 0;
        }
     }
    if(clickNumbers % 2 == 0) drawElipse(s1,s2,r1,r2);
    update();
}

void MainWindow::obrot(int a)
{
    im.fill(0xFFFFFF);
    beta = qDegreesToRadians((double)a);
    drawElipse(s1,s2,r1,r2);
    update();
}

void MainWindow::onColorChanged()
{
    //Ustawiamy kolory, jakie miała elipsa podczas poprzedniego rysowania
    re1 = tab[0];
    ge1 = tab[1];
    be1 = tab[2];
    re2 = tab[3];
    ge2 = tab[4];
    be2 = tab[5];
    //Sprawdzamy, ktora połowe elipsy mamy pokolorowac
    if(ui->cb1->isChecked()){
    re1 = ui->redSlider->value();
    ge1 = ui->greenSlider->value();
    be1 = ui->blueSlider->value();
    }
    if(ui->cb2->isChecked()){
        re2 = ui->redSlider->value();
        ge2 = ui->greenSlider->value();
        be2 = ui->blueSlider->value();
    }
    if(ui->cb1->isChecked() && ui->cb2->isChecked()){
        re1 = ui->redSlider->value();
        ge1 = ui->greenSlider->value();
        be1 = ui->blueSlider->value();
        re2 = ui->redSlider->value();
        ge2 = ui->greenSlider->value();
        be2 = ui->blueSlider->value();
    }
    //Aktualizacja koloru na widgecie
    m_color.setRgb(ui->redSlider->value(),ui->greenSlider->value(),ui->blueSlider->value());
    QPalette pal = ui->displayWidget->palette();
    pal.setColor(QPalette::Window,m_color);
    ui->displayWidget->setPalette(pal);
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

void MainWindow::drawElipse(int s1, int s2, int r1, int r2){
    int N = 10;
    for(double t=0; t<=N; t++){
        double alpha = 2*M_PI*t/N;
        x1 = r1*qCos(alpha);
        y1 = r2*qSin(alpha);
        obt1 = x1*qCos(beta)-y1*qSin(beta);
        obt2 = x1*qSin(beta)+y1*qCos(beta);
        if(t==0){
            obo1 = obt1;
            obo2 = obt2;
        }else{
            if(t<=N/2){
                drawSegment(obo1+s1,obo2+s2,obt1+s1,obt2+s2, col1);
                //Przechowujemy poprzedni punkt
                obo1 = obt1;
                obo2 = obt2;
            }
            else{
                drawSegment(obo1+s1,obo2+s2,obt1+s1,obt2+s2, col2);
                //Przechowujemy poprzedni punkt
                obo1 = obt1;
                obo2 = obt2;
            }
        }
    }
    //Zapisujemy stan kolorow
    tab[0] = re1;
    tab[1] = ge1;
    tab[2] = be1;
    tab[3] = re2;
    tab[4] = ge2;
    tab[5] = be2;
}

void MainWindow::swap(double &x, double &y){
    double tmp = x;
    x = y;
    y = tmp;
}

void MainWindow::drawSegment(double x1, double y1, double x2, double y2,int zm)
{
    if(zm == 1){
        r = re1;
        g = ge1;
        b = be1;
    }
    else if(zm == 2) {
        r = re2;
        g = ge2;
        b = be2;
    }
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
