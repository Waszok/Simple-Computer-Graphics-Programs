#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setMinimumSize(700,520);

    width = 500;
    height = 500;
    img = QImage(width, height, QImage::Format_RGB32);
    img.fill(0xFFFFFF);

    //TextBlocki do wprowadzenia wspolrzednych wektora translacji:
    CorX = new QLineEdit(this);
    CorX ->setGeometry(550, 20, 50, 40);
    CorY = new QLineEdit(this);
    CorY ->setGeometry(550, 80, 50, 40);
    connect(CorX, SIGNAL(textChanged(QString)), this, SLOT(gotCorX()));
    connect(CorY, SIGNAL(textChanged(QString)), this, SLOT(gotCorY()));

    translacja = new QPushButton(this);
    translacja->setGeometry(550, 140, 100, 30);
    translacja->setText("Translacja");
    connect(translacja, SIGNAL(clicked(bool)), this, SLOT(translateBtn()));
    skalowanie = new QPushButton(this);
    skalowanie->setGeometry(550, 180, 100, 30);
    skalowanie->setText("Skalowanie");
    connect(translacja, SIGNAL(clicked(bool)), this, SLOT(scaleBtn()));

    //Labels - teksty "X", "Y":
    x_text = new QLabel("X: ", this);
    x_text ->setGeometry(520, 20, 50, 40);
    QFont font = x_text->font();
    font.setBold(true);
    font.setPointSize(10);
    font.setItalic(true);
    x_text->setFont(font);
    y_text = new QLabel("Y: ", this);
    y_text ->setGeometry(520, 80, 50, 40);
    font = y_text->font();
    font.setBold(true);
    font.setPointSize(10);
    font.setItalic(true);
    y_text->setFont(font);

    //Translacja:
    text_translacja = new QLabel("Translacja: ", this);
    text_translacja ->setGeometry(520, 220, 150, 30);
    font = text_translacja->font();
    font.setBold(true);
    font.setPointSize(10);
    text_translacja->setFont(font);
    translacjaTX = new QSlider(Qt::Orientation::Horizontal, this);
    translacjaTX->setGeometry(520, 260, 150, 20);
    translacjaTX->setMinimum(-100);
    translacjaTX->setMaximum(100);
    translacjaTX->setSingleStep(1);
    translacjaTX->setSliderPosition(0);
    translacjaTY = new QSlider(Qt::Orientation::Horizontal, this);
    translacjaTY->setGeometry(520, 290, 150, 20);
    translacjaTY->setMinimum(-100);
    translacjaTY->setMaximum(100);
    translacjaTY->setSingleStep(1);
    translacjaTY->setSliderPosition(0);
    connect(translacjaTX, SIGNAL(valueChanged(int)), this, SLOT(translationChange()));
    connect(translacjaTY, SIGNAL(valueChanged(int)), this, SLOT(translationChange()));

    //Skalowanie:
    text_skalowanie = new QLabel("Skalowanie: ", this);
    text_skalowanie ->setGeometry(520, 330, 150, 30);
    font = text_skalowanie->font();
    font.setBold(true);
    font.setPointSize(10);
    text_skalowanie->setFont(font);
    skalowanieSX = new QSlider(Qt::Orientation::Horizontal, this);
    skalowanieSX->setGeometry(520, 370, 150, 20);
    skalowanieSX->setMinimum(10);
    skalowanieSX->setMaximum(400);
    skalowanieSX->setSingleStep(1);
    skalowanieSX->setSliderPosition(100);
    skalowanieSY = new QSlider(Qt::Orientation::Horizontal, this);
    skalowanieSY->setGeometry(520, 400, 150, 20);
    skalowanieSY->setMinimum(10);
    skalowanieSY->setMaximum(400);
    skalowanieSY->setSingleStep(1);
    skalowanieSY->setSliderPosition(100);
    connect(skalowanieSX, SIGNAL(valueChanged(int)), this, SLOT(scaleChange()));
    connect(skalowanieSY, SIGNAL(valueChanged(int)), this, SLOT(scaleChange()));

    //Rotacja:
    text_rotacja = new QLabel("Rotacja: ", this);
    text_rotacja ->setGeometry(520, 440, 150, 30);
    font = text_rotacja->font();
    font.setBold(true);
    font.setPointSize(10);
    text_rotacja->setFont(font);
    rotacjaS = new QSlider(Qt::Orientation::Horizontal, this);
    rotacjaS->setGeometry(520, 480, 150, 20);
    rotacjaS->setMinimum(0);
    rotacjaS->setMaximum(360);
    rotacjaS->setSingleStep(1);
    connect(rotacjaS, SIGNAL(valueChanged(int)), this, SLOT(rotationChange()));

    //Punkty tworzace figure:
    p.x = 120;
    p.y = 70;
    listOfPoints.push_back(p);
    p.x = 150;
    p.y = 70;
    listOfPoints.push_back(p);
    p.x = 190;
    p.y = 350;
    listOfPoints.push_back(p);
    p.x = 80;
    p.y = 350;
    listOfPoints.push_back(p);
    p.x = 80;
    p.y = 120;
    listOfPoints.push_back(p);
    p.x = 150;
    p.y = 130;
    listOfPoints.push_back(p);

    r = 0; g = 0; b = 0;
    tx = 0; ty = 0; sx = 1; sy = 1; alpha = 0;
    corx = 0; cory = 0;

    drawFigure(listOfPoints);

    T = {{1, 0, tx},
         {0, 1, ty},
         {0, 0, 1}};

    S = {{sx, 0, 0},
         {0, sy, 0},
         {0, 0, 1}};

    R = {{+cos(alpha), -sin(alpha), 0},
         {+sin(alpha), +cos(alpha), 0},
         {0, 0, 1}};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(10, 10, img);
}

void MainWindow::putPixel(int x, int y)
{
    if(x >= 0 && x < width && y >= 0 && y < height){
        pix = img.scanLine(y);
        pix[x*4] = b;
        pix[x*4 + 1] = g;
        pix[x*4 + 2] = r;
    }
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

void MainWindow::drawFigure(vector<Ui::Point> listOfPoints){
    for(uint i = 0; i < listOfPoints.size(); i++){
        putPixel(listOfPoints[i].x, listOfPoints[i].y);
        drawSegment(listOfPoints[i].x, listOfPoints[i].y,
                    listOfPoints[(i+1)%listOfPoints.size()].x, listOfPoints[(i+1)%listOfPoints.size()].y);
    }
}

void MainWindow::redrawFigure()
{
    img.fill(0xFFFFFF);
    M = T * S * R;
    //M.print();
    mat wektorTmp(3, 1);
    mat wektorWyn(3, 1);
    Ui::Point tmp;
    vector<Ui::Point> listTmp;
    for(uint i = 0; i<listOfPoints.size(); i++){
        wektorTmp(0, 0) = listOfPoints[i].x;
        wektorTmp(1, 0) = listOfPoints[i].y;
        wektorTmp(2, 0) = 1;
        wektorWyn = M * wektorTmp;
        tmp.x = wektorWyn(0,0); tmp.y=wektorWyn(1,0);
        listTmp.push_back(tmp);
    }
    drawFigure(listTmp);
    update();
}

void MainWindow::gotCorX()
{
    corx = CorX->text().toDouble();
}

void MainWindow::gotCorY()
{
    cory = CorY->text().toDouble();
}

void MainWindow::translateBtn()
{
    img.fill(0xFFFFFF);
    tx = corx;
    ty= cory;
    T(0, 2) = tx;
    T(1, 2) = ty;
    T.print();
    redrawFigure();
    update();
}

void MainWindow::scaleBtn()
{
    img.fill(0xFFFFFF);
    sx = corx;
    sy= cory;
    S(0, 0) = sx;
    S(1, 1) = sy;
    redrawFigure();
    update();
}

void MainWindow::translationChange()
{
    tx = translacjaTX->value();
    ty = translacjaTY->value();
    T(0, 2) = tx;
    T(1, 2) = ty;
    T.print();
    redrawFigure();
}

void MainWindow::scaleChange()
{
    sx = skalowanieSX->value();
    sy = skalowanieSY->value();
    mat Tpom1 = {{1, 0, 130},
                {0, 1, 235},
                {0, 0, 1}};
    mat Tpom2 ={{1, 0, -130},
                {0, 1, -235},
                {0, 0, 1}};
    S.eye();
    S(0, 0) = sx/100;
    S(1, 1) = sy/100;
    S = Tpom1 * S * Tpom2;
    redrawFigure();
}

void MainWindow::rotationChange()
{
    alpha = rotacjaS->value()*2*M_PI/360;
    mat Tpom1 = {{1, 0, 130},
                {0, 1, 235},
                {0, 0, 1}};
    mat Tpom2 ={{1, 0, -130},
                {0, 1, -235},
                {0, 0, 1}};
    //qDebug("%f %f %f %f", cos(alpha), -sin(alpha), sin(alpha), cos(alpha));
    R.eye();
    R(0, 0) = cos(alpha);
    R(0, 1) = -sin(alpha);
    R(1, 0) = sin(alpha);
    R(1, 1) = cos(alpha);
    //R.print();
    //mat P;
    R = Tpom1 * R * Tpom2;
    //R = P;
    //R = Tpom1 * R * Tpom2;;
    redrawFigure();
}
