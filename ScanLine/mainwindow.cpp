#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setMinimumSize(910,800);


    width = 710;
    height = 600;
    im = QImage(width, height, QImage::Format_RGB32);
    im.fill(0xFFFFFF);

    QString path = QFileDialog::getOpenFileName();
    QImage obr(path);
            QPainter pa(&im);
            pa.drawImage(0,0, obr);
            pa.end();
    imKopia = QImage(width, height, QImage::Format_RGB32);
    memcpy( imKopia.bits(), im.bits(), width * height * 4 );
    //if(!path.isNull)

    //}


    //Otwarcie:
    otwarcie = new QPushButton("otwarcie", this);
    otwarcie->setGeometry(720, 380, 175, 40);
    otwarcie->setText("Otwarcie");
    connect(otwarcie, SIGNAL(pressed()), this, SLOT(pressOtwarcie()));

    //Domkniecie:
    domkniecie = new QPushButton("domkniecie", this);
    domkniecie->setGeometry(720, 430, 175, 40);
    domkniecie->setText("Domkniecie");
    connect(domkniecie, SIGNAL(pressed()), this, SLOT(pressDomkniecie()));

    //Dylatacja:
    dylatacja = new QPushButton("dylatacja", this);
    dylatacja->setGeometry(720, 330, 175, 40);
    dylatacja->setText("Dylatacja");
    connect(dylatacja, SIGNAL(pressed()), this, SLOT(pressDylatacja()));

    //Erozja:
    erozja = new QPushButton("erozja", this);
    erozja->setGeometry(720, 280, 175, 40);
    erozja->setText("Erozja");
    connect(erozja, SIGNAL(pressed()), this, SLOT(pressErozja()));

    //Wybor koloru:
    wybierz = new QPushButton("wybierz", this);
    wybierz->setGeometry(720, 20, 175, 40);
    wybierz->setText("Wybierz kolor");
    connect(wybierz, SIGNAL(pressed()), this, SLOT(wybierzKolor()));

    //Czyszczenie ekranu:
    czysc = new QPushButton("czysc", this);
    czysc->setGeometry(720, 70, 175, 40);
    czysc->setText("Wyczyść ekran");
    connect(czysc, SIGNAL(clicked(bool)), this, SLOT(czyscEkran()));

    //Potwierdzenie wyboru współrzędnych:
    ok = new QPushButton("ok", this);
    ok->setGeometry(720, 220, 175, 40);
    ok->setText("Potwierdź");
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(potwierdz()));

    //QLineEdits - wprowadzanie współrzędnych z klawiatury:
    x_wsp = new QLineEdit(this);
    x_wsp ->setGeometry(750, 170, 50, 40);
    y_wsp = new QLineEdit(this);
    y_wsp ->setGeometry(840, 170, 50, 40);
    connect(x_wsp, SIGNAL(textChanged(QString)), this, SLOT(dodanoX()));
    connect(y_wsp, SIGNAL(textChanged(QString)), this, SLOT(dodanoY()));

    //Labels - teksty "X", "Y":
    x_text = new QLabel("X: ", this);
    x_text ->setGeometry(720, 170, 50, 40);
    QFont font = x_text->font();
    font.setBold(true);
    font.setPointSize(10);
    font.setItalic(true);
    x_text->setFont(font);
    y_text = new QLabel("Y: ", this);
    y_text ->setGeometry(810, 170, 50, 40);
    QFont font2 = y_text->font();
    font2.setBold(true);
    font2.setPointSize(10);
    font2.setItalic(true);
    y_text->setFont(font2);

    //Label - tekst nad wspolrzednymi:
    text = new QLabel("Podaj współrzędne punktu: ", this);
    text ->setGeometry(710, 130, 195, 40);
    QFont font3 = text->font();
    font3.setBold(true);
    font3.setPointSize(7);
    font3.setItalic(true);
    text->setFont(font3);

//Pierwsza figura do testow:
//    p.x = 100;
//    p.y = 400;
//    moj.push_back(p);
//    p.x = 120;
//    p.y = 280;
//    moj.push_back(p);
//    p.x = 180;
//    p.y = 280;
//    moj.push_back(p);
//    p.x = 180;
//    p.y = 220;
//    moj.push_back(p);
//    p.x = 180;
//    p.y = 120;
//    moj.push_back(p);
//    p.x = 130;
//    p.y = 150;
//    moj.push_back(p);
//    p.x = 110;
//    p.y = 170;
//    moj.push_back(p);
//    scanLines();

//Druga figura do testow:
        p.x = 120;
        p.y = 70;
        moj.push_back(p);
        p.x = 150;
        p.y = 70;
        moj.push_back(p);
        p.x = 190;
        p.y = 350;
        moj.push_back(p);
        p.x = 80;
        p.y = 350;
        moj.push_back(p);
        p.x = 80;
        p.y = 120;
        moj.push_back(p);
        p.x = 150;
        p.y = 130;
        moj.push_back(p);
        //scanLines();
        //QPainterPath path;
        //path.moveTo(20, 80);
        //path.lineTo(20, 30);
        //path.cubicTo(80, 0, 50, 50, 80, 80);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
     memcpy( im.bits(), imKopia.bits(), width * height * 4 );
     p.drawImage(0, 0, imKopia);
     //p.drawPixmap(0, 0, 150, 150, pixmap1);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton && e->x() < width && e->y() < height && e->x() > 0 && e->y() > 0){
        p.x = e->x();
        p.y = e->y();
        moj.push_back(p);
        imKopia.fill(0xFFFFFF);
        scanLines();
    }
    else{
        qDebug("Probujesz wyznaczyc punkt poza obszarem!!!");
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){

    }
    update();
}

void MainWindow::wybierzKolor()
{
    c = QColorDialog::getColor();
}

void MainWindow::czyscEkran()
{
    im.fill(0xFFFFFF);
    moj.clear();
    qDebug("%d", moj.size());
    update();
}

void MainWindow::dodanoX()
{
    p.x = (x_wsp->text()).toInt();
}

void MainWindow::dodanoY()
{
    p.y = (y_wsp->text()).toInt();
}

void MainWindow::pressDylatacja(){
    dylatacja_function();
}

void MainWindow::pressErozja(){
    erozja_function();
}

void MainWindow::pressOtwarcie(){
    otwarcie_function();
}

void MainWindow::pressDomkniecie(){
    domkniecie_function();
}

void MainWindow::potwierdz()
{
    qDebug("%d %d", p.x, p.y);
    if(p.x > 0 && p.y > 0 && p.x < width && p.y < height){
        moj.push_back(p);
        im.fill(0xFFFFFF);
        scanLines();
    }
    else{
        qDebug("Podano niewłaściwe wpółrzędne!!!");
    }
}

void MainWindow::putPixel(int x, int y)
{
    if(x >= 0 && x < width && y >= 0 && y < height){
        pix = imKopia.scanLine(y);
        pix[x*4] = c.blue();
        pix[x*4 + 1] = c.green();
        pix[x*4 + 2] = c.red();
        //pix[x*4 + 3] = c.alpha();
    }
}

void MainWindow::scanLines(){
    //Znajdujemy ymin i ymax:
    findMinMax();
    //Rysujemy kontur figury ktora chcemy wypelnic:
    for(int i = 0; i < moj.size(); i++){
        putPixel(moj[i].x, moj[i].y);
        //drawSegment(moj[i].x, moj[i].y, moj[(i+1)%moj.size()].x, moj[(i+1)%moj.size()].y);
    }
    //Algorytm ScanLine:
    for(int j = ymin; j < ymax; j++){
        for(int i = 0; i < moj.size(); i++){
            if(moj[i].y == moj[(i+1)%moj.size()].y) //&& j == moj[i].y
            {
                //tablica_pp.push_back(x);
                //tablica_pp.push_back(x);
                continue;
            }
            wsp =(j - moj[i].y)/(double)(moj[(i+1)%moj.size()].y-moj[i].y);
            x = (double)((1- wsp)*moj[i].x + wsp*moj[(i+1)%moj.size()].x);
            if((moj[i].y >= moj[(i+1)%moj.size()].y && j <= moj[i].y && j >= moj[(i+1)%moj.size()].y) ||
               (moj[i].y < moj[(i+1)%moj.size()].y && j <= moj[(i+1)%moj.size()].y && j >= moj[i].y))
            {
                int tmp = 0;
                int l = i;
                int a = i - 1;
                int czy_juz_jest = 0;
                p.x = x;
                p.y = j;
                for(int k=0; k<tablica_pp.size(); k++){
                    if(p.x == tablica_pp[k]) czy_juz_jest = 1;
                }
                for(int w = 0; w<moj.size(); w++){
                    if(p.x == moj[w].x && p.y == moj[w].y){
                        tmp = 1;
                        if(w != 0){
                            l = w;
                            a = l - 1;
                        }
                        else if(w == 0){
                            a = moj.size() - 1;
                        }
                        break;
                    }
                }

                if(czy_juz_jest == 0){
                    if((tmp == 1 && moj[a].y > p.y && moj[(l+1)%moj.size()].y > p.y) ||
                       (tmp == 1 && moj[a].y < p.y && moj[(l+1)%moj.size()].y < p.y)){
                        tablica_pp.push_back(x);
                        tablica_pp.push_back(x);
                    }
                    else {
                        tablica_pp.push_back(x);
                    }
                }
            }
        }
        std::sort(tablica_pp.begin(), tablica_pp.end());
        for(int k = 0; k < tablica_pp.size() - 1; k+=2){
           drawHorizontalLine(tablica_pp[k], tablica_pp[k+1], j);
        }

        tablica_pp.clear();
    }
    update();
}

void MainWindow::swap(int &x, int &y){
    double tmp = x;
    x = y;
    y = tmp;
}

void MainWindow::drawHorizontalLine(double x1, double x2, double y)
{
    for(int i = x1; i <= x2; i++){
        if(i > 0 && y > 0 && i < width && y < height){
            putPixel(i, y);
        }
    }
}

void MainWindow::findMinMax()
{
    ymin = moj[0].y;
    ymax = moj[0].y;
    for(uint i=1; i< moj.size(); i++){
          if(moj[i].y < ymin) ymin = moj[i].y;
          if(moj[i].y >= ymax) ymax = moj[i].y;
    }
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

//Morfologia

void MainWindow::erozja_function(){
    uint32_t *bit = (uint32_t*)im.bits();
    uint32_t *bitKopia = (uint32_t*)imKopia.bits();
    unsigned int kolor = 0xFFFFFF;

    for ( int i = 1; i < width * height - 1; i++){
        if ( (bit[i-1]&0xffffff) == kolor || (bit[i+1]&0xffffff) == kolor || (i-width > 0 && (bit[i-width]&0xffffff) == kolor)
             || (i+width < width*height && bit[i+width]&0xffffff == kolor) ||
             (i - 1 - width > 0 && (bit[i-width - 1]&0xffffff) == kolor) || (i - width + 1> 0 && (bit[i-width +1 ]&0xffffff) == kolor)
             || (i - 1 + width < width*height && (bit[i - 1 + width]&0xffffff) == kolor) ||
             (i + 1 + width < width * height && (bit[i + 1 + width]&0xffffff) == kolor))
            bitKopia[i] = kolor;
    }
    repaint();
}

void MainWindow::otwarcie_function()
{
    erozja_function();
    dylatacja_function();
}

void MainWindow::domkniecie_function()
{
    dylatacja_function();
    erozja_function();
}

void MainWindow::dylatacja_function(){
    uint32_t *bit = (uint32_t*)im.bits();
    uint32_t *bitKopia = (uint32_t*)imKopia.bits();
    unsigned int kolor = 0x000000;

    for (int i = 1; i < width * height - 1; i++){
        int j = i/width;
        //qDebug("%d", j);
        if ( ((bit[i-1]&0xffffff) == kolor && (i-1) > j*width) || ((bit[i+1]&0xffffff) == kolor && ((i+1) < (j+1)*width - 1)) /*|| (i-width > 0 && (bit[i-width]&0xffffff) == kolor)
             || (i+width < width*height && (bit[i+width]&0xffffff) == kolor) ||
             (i - 1 - width > 0 && (bit[i-width - 1]&0xffffff) == kolor) || (i - width + 1> 0 && (bit[i-width +1 ]&0xffffff) == kolor)
             || (i - 1 + width < width*height && (bit[i - 1 + width]&0xffffff) == kolor) ||
             (i + 1 + width < width * height && (bit[i + 1 + width]&0xffffff) == kolor)*/)
            bitKopia[i] = kolor;
    }
    repaint();
}
