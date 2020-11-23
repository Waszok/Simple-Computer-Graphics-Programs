#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setMinimumSize(900,800);

    width = 710;
    height = 600;
    im = QImage(width, height, QImage::Format_RGB32);
    im.fill(Qt::white);


//    QImage obr("easter");
//    if(obr.isNull()){
//        qDebug("Obrazek nie zaladowal sie.");
//        exit(-1);
//    }

//    QPainter p(&im);
//    p.drawImage(100, 100, im);
//    p.end();

    wybierz = new QPushButton("wybierz", this);
    wybierz->setGeometry(720, 20, 175, 40);
    wybierz->setText("Wybierz kolor");

    im.fill(0xFFFFFF);

    drawCircle(250, 250, 200);
    connect(wybierz, SIGNAL(pressed()), this, SLOT(wybierzKolor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 0, im);
}

void MainWindow::wybierzKolor()
{
    c = QColorDialog::getColor();
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        qDebug("ccccccccccc");
        //flood_fill(e->x(), e->y(), color);
        flood_fill_2(e->x(), e->y(), c);

    }
    qDebug("%d %d", e->x(), e->y());
    update();
}

//void MainWindow::flood_fill(int x, int y, Ui::Kolorek color)
//{
//    bg = im.pixelColor(x, y);
//    flood_fill_rec(x, y, color, bg);
//}

//void MainWindow::flood_fill_rec(int x, int y, Ui::Kolorek color, QColor bg)
//{
//    if(x<1 || y<1 || x> width+1 || y > height+1) return;
//    if(im.pixelColor(x,y) != bg) return;
//    putPixel(x,y);
//    flood_fill_rec(x-1,y,color,bg);
//    flood_fill_rec(x+1,y,color,bg);
//    flood_fill_rec(x,y-1,color,bg);
//    flood_fill_rec(x,y+1,color,bg);
//}

void MainWindow::putPixel(int x, int y)
{
    if(x > 0 && x < width && y > 0 && y < height){
        pix = im.scanLine(y);
        pix[x*4] = c.blue();
        pix[x*4 + 1] = c.green();
        pix[x*4 + 2] = c.red();
    }
}

void MainWindow::drawCircle(int x0, int y0, double r)
{
    for(int y=0; y<=r/sqrt(2); y++){
        double iks = sqrt(r*r-y*y);
        putPixel(iks+x0,y+y0);
        putPixel(y+x0,-iks+y0);
        putPixel(-iks+x0,-y+y0);
        putPixel(-y+x0,iks+y0);
        putPixel(y+x0,iks+y0);
        putPixel(iks+x0,-y+y0);
        putPixel(-y+x0,-iks+y0);
        putPixel(-iks+x0,y+y0);
    }
}

void MainWindow::flood_fill_2(int x, int y, QColor c)
{
    Ui::Punkt p;
    bg = im.pixelColor(x, y);
    if(bg == c) return;
    std::stack<Ui::Punkt> pts;
    p.x = x;
    p.y = y;
    pts.push(p);
    while (!pts.empty()){
        p = pts.top();
        pts.pop();
        putPixel(p.x,p.y);
        for (int i =-1; i<2; i+=2){
            if (p.x+i > 0 && p.x+i < width && p.y > 0 && p.y < height && im.pixelColor(p.x+i, p.y) == bg){
                Ui::Punkt p1;
                p1.x = p.x+i;
                p1.y = p.y;
                pts.push(p1);
                putPixel(p.x+i, p.y);
            }
        }
        for (int j=-1; j<2; j+=2){
            if (p.x > 0 && p.x < width && p.y+j > 0 && p.y+j < height &&  im.pixelColor(p.x, p.y+j) == bg){
                Ui::Punkt p2;
                p2.x = p.x;
                p2.y = p.y + j;
                pts.push(p2);
                putPixel(p.x, p.y+j);
            }
        }
    }
    update();
}
