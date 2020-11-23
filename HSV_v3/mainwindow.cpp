#include "mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setMinimumSize(800, 450);
    width = 400;
    height = 400;
    img = QImage(width, height, QImage::Format_RGB32);
    img.fill(0xFFFFFF);
    img2 = QImage(40, 360, QImage::Format_RGB32);
    img2.fill(0xFFFFFF);

    suwaki = new QWidget(this);
    slideryLayout = new QFormLayout(suwaki);
    sliderR = new QSlider(Qt::Horizontal);
    sliderG = new QSlider(Qt::Horizontal);
    sliderB = new QSlider(Qt::Horizontal);
    sliderH = new QSlider(Qt::Horizontal);
    sliderS = new QSlider(Qt::Horizontal);
    sliderV = new QSlider(Qt::Horizontal);
    sliderR -> setFixedSize(125, 23);
    sliderG -> setFixedSize(125, 23);
    sliderB -> setFixedSize(125, 23);
    sliderH -> setFixedSize(125, 23);
    sliderS -> setFixedSize(125, 23);
    sliderV -> setFixedSize(125, 23);
    sliderR -> setMaximum(255);
    sliderG -> setMaximum(255);
    sliderB -> setMaximum(255);
    sliderH -> setMaximum(359);
    sliderS -> setMaximum(100);
    sliderV -> setMaximum(100);
    labelR = new QLabel("R 0");
    labelG = new QLabel("G 0");
    labelB = new QLabel("B 0");
    labelH = new QLabel("H 0");
    labelS = new QLabel("S 0");
    labelV = new QLabel("V 0");

    slideryLayout -> addRow(sliderR, labelR);
    slideryLayout -> addRow(sliderG, labelG);
    slideryLayout -> addRow(sliderB, labelB);
    slideryLayout -> addRow(sliderH, labelH);
    slideryLayout -> addRow(sliderS, labelS);
    slideryLayout -> addRow(sliderV, labelV);
    suwaki -> setGeometry(480, 90, 220, 200);

    R = 0; G = 0; B = 0; hue = 0; sat = 0; val = 0;

    connect(sliderR, SIGNAL(valueChanged(int)), this, SLOT(zmianaRGB()));
    connect(sliderG, SIGNAL(valueChanged(int)), this, SLOT(zmianaRGB()));
    connect(sliderB, SIGNAL(valueChanged(int)), this, SLOT(zmianaRGB()));
    connect(sliderH, SIGNAL(valueChanged(int)), this, SLOT(zmianaHSV()));
    connect(sliderS, SIGNAL(valueChanged(int)), this, SLOT(zmianaHSV()));
    connect(sliderV, SIGNAL(valueChanged(int)), this, SLOT(zmianaHSV()));

    drawH();
    drawSV();
}

MainWindow::~MainWindow(){
    delete sliderB;
    delete sliderG;
    delete sliderH;
    delete sliderR;
    delete sliderS;
    delete sliderV;
    delete labelB;
    delete labelG;
    delete labelH;
    delete labelR;
    delete labelS;
    delete labelV;
    delete slideryLayout;
    delete suwaki;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawImage(10, 10, img);
    painter.drawImage(430, 30, img2);
}

void MainWindow::rgb2hsv(float r, float g, float b){
    float rtmp, gtmp, btmp, cmax, cmin, delta;
    float h, s, v;
    rtmp = r/255;
    gtmp = g/255;
    btmp = b/255;
    cmax = MAX(rtmp, gtmp, btmp);
    cmin = MIN(rtmp, gtmp, btmp);
    delta = cmax - cmin;
    if(delta == 0){
        h = 0;
    }
    else if(cmax == rtmp){
        h = 60*(fmod((gtmp- btmp)/delta, 6));
    }
    else if(cmax == gtmp){
        h = 60*((btmp - rtmp)/delta + 2);
    }
    else if(cmax == btmp){
        h = 60*((rtmp - gtmp)/delta + 4);
    }
    if(cmax == 0){
        s = 0;
    }
    else{
        s = 100*(delta/cmax);
    }
    v = 100*cmax;
    hue = round(h);
    sat = round(s);
    val = round(v);
    update();
}

void MainWindow::hsv2rgb(float hue, float sat, float val)
{
    float c, x, m, rtmp, gtmp, btmp;
    c = (val/100) * (sat/100);
    x = c * (1 - abs(fmod(hue/60, 2) - 1));
    m = val/100 - c;
    if(hue >= 0 && hue < 60 ){
        rtmp = c;
        gtmp = x;
        btmp = 0;
    }
    if(hue >= 60 && hue < 120){
        rtmp = x;
        gtmp = c;
        btmp = 0;
    }
    if(hue >= 120 && hue < 180){
        rtmp = 0;
        gtmp = c;
        btmp = x;
    }
    if(hue >= 180 && hue < 240){
        rtmp = 0;
        gtmp = x;
        btmp = c;
    }
    if(hue >= 240 && hue < 300){
        rtmp = x;
        gtmp = 0;
        btmp = c;
    }
    if(hue >= 300 && hue < 360){
        rtmp = c;
        gtmp = 0;
        btmp = x;
    }
    rtmp = round(255*(rtmp + m));
    gtmp = round(255*(gtmp + m));
    btmp = round(255*(btmp + m));
    R = rtmp;
    G = gtmp;
    B = btmp;
    update();
}

void MainWindow::drawH()
{
    for(int y = 0; y <= 360; y++){
        hsv2rgb(y, 100, 100);
        drawHorizontalLine(y, 0, 40);
    }
    R = sliderR->value();
    G = sliderG->value();
    B = sliderB->value();
    drawHorizontalLineOn((int)hue, 0, 40);
    update();
}

void MainWindow::drawSV()
{
    for(int s = 0; s<= 400; s++){
        for(int v = 400; v>=0; v--){
            sat = s/4;
            val = abs(100 - v/4);
            //sliderH->blockSignals(true);
            //sliderS->blockSignals(true);
            //sliderV->blockSignals(true);
            hsv2rgb(hue, sat, val);
            //sliderH->blockSignals(false);
            //sliderS->blockSignals(false);
            //sliderV->blockSignals(false);
            putPixel(s, v ,R ,G ,B, img);
        }
    }
    sat = sliderS->value();
    val = sliderV->value();
    drawCircle((int)sat * 4, 400 - (int)val * 4);
    update();
}

void MainWindow::drawHorizontalLine(int y, int x1, int x2)
{
    for(int i = x1; i <= x2; i++){
        putPixel(i, y, R, G, B, img2);
    }
}

void MainWindow::drawHorizontalLineOn(int y, int x1, int x2)
{
    for(int i = x1; i <= x2; i++){
        putPixel(i, y, 0, 0, 0, img2);
    }
}

void MainWindow::drawCircle(int x0, int y0)
{
    int red, green, blue;
    if(val > 50){
        red = 0;
        green = 0;
        blue = 0;
    }
    else{
        red = 255;
        green = 255;
        blue = 255;
    }
    int r = 5;
    for(int y=0; y<=r/sqrt(2); y++){
        double iks = sqrt(r*r-y*y);
        putPixel(iks+x0,y+y0, red, green, blue, img);
        putPixel(y+x0,-iks+y0, red, green, blue, img);
        putPixel(-iks+x0,-y+y0, red, green, blue, img);
        putPixel(-y+x0,iks+y0, red, green, blue, img);
        putPixel(y+x0,iks+y0, red, green, blue, img);
        putPixel(iks+x0,-y+y0, red, green, blue, img);
        putPixel(-y+x0,-iks+y0, red, green, blue, img);
        putPixel(-iks+x0,y+y0, red, green, blue, img);
    }
}

void MainWindow::putPixel(int x, int y, int r, int g, int b, QImage &im)
{
    if(x >= 0 && x < im.width() && y >= 0 && y < im.height()){
        uchar *pix = im.scanLine(y);
        pix[x*4] = b;
        pix[x*4 + 1] = g;
        pix[x*4 + 2] = r;
    }
}

void MainWindow::zmianaRGB()
{
    labelR -> setText("R " + QString::number(sliderR->value()));
    R = sliderR->value();
    labelG -> setText("G " + QString::number(sliderG->value()));
    G = sliderG->value();
    labelB -> setText("B " + QString::number(sliderB->value()));
    B = sliderB->value();

    rgb2hsv(R, G, B);

    sliderH->blockSignals(true);
    sliderS->blockSignals(true);
    sliderV->blockSignals(true);

    sliderH->setValue(hue);
    labelH -> setText("H " + QString::number(sliderH->value()));
    sliderS->setValue(sat);
    labelS -> setText("S " + QString::number(sliderS->value()));
    sliderV->setValue(val);
    labelV -> setText("V " + QString::number(sliderV->value()));

    sliderH->blockSignals(false);
    sliderS->blockSignals(false);
    sliderV->blockSignals(false);

    img.fill(0xFFFFFF);
    drawSV();
    img2.fill(0xFFFFFF);
    drawH();
    update();
}

void MainWindow::zmianaHSV()
{
    labelH -> setText("H " + QString::number(sliderH->value()));
    hue = sliderH->value();
    labelS -> setText("S " + QString::number(sliderS->value()));
    sat = sliderS->value();
    labelV -> setText("V " + QString::number(sliderV->value()));
    val = sliderV->value();

    hsv2rgb(hue, sat, val);

    sliderR->blockSignals(true);
    sliderG->blockSignals(true);
    sliderB->blockSignals(true);

    sliderR->setValue(R);
    labelR -> setText("R " + QString::number(sliderR->value()));
    sliderG->setValue(G);
    labelG -> setText("G " + QString::number(sliderG->value()));
    sliderB->setValue(B);
    labelB -> setText("B " + QString::number(sliderB->value()));

    sliderR->blockSignals(false);
    sliderG->blockSignals(false);
    sliderB->blockSignals(false);

    img.fill(0xFFFFFF);
    drawSV();
    img2.fill(0xFFFFFF);
    drawH();
    update();
}

