#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this -> setMinimumSize(700, 450);
    width = 400;
    height = 400;
    img = QImage(width, height, QImage::Format_RGB32);
    newImg = QImage(width, height, QImage::Format_RGB32);
    img.fill(0xFFFFFF);
    counter = 0;

    picture1 = QImage("tree.jpg");
    if(picture1.isNull()){
        qDebug("error");
    }
    picture2 = QImage("apple");
    if(picture2.isNull()){
        qDebug("error");
    }
    picture3 = QImage("people");
    if(picture3.isNull()){
        qDebug("error");
    }
    QPainter p(&img);
    p.drawImage(0, 0, picture1);
    p.end();

    layer2 = new QCheckBox("Layer 2", this);
    layer2->setGeometry(420, 120, 150, 30);
    layer3 = new QCheckBox("Layer 3", this);
    layer3->setGeometry(420, 160, 150, 30);
    group_layerBtn = new QButtonGroup(this);
    group_layerBtn->addButton(layer2);
    group_layerBtn->addButton(layer3);
    group_layerBtn->setExclusive(true);

    normal = new QPushButton(this);
    normal->setGeometry(420, 200, 150, 30);
    normal->setText("Normal");
    multiply = new QPushButton(this);
    multiply->setGeometry(420, 230, 150, 30);
    multiply->setText("Multiply");
    darken = new QPushButton(this);
    darken->setGeometry(420, 260, 150, 30);
    darken->setText("Darken");
    lighten = new QPushButton(this);
    lighten->setGeometry(420, 290, 150, 30);
    lighten->setText("Lighten");
    overlay = new QPushButton(this);
    overlay->setGeometry(420, 320, 150, 30);
    overlay->setText("Overlay");

    alphaSlider = new QSlider(Qt::Horizontal, this);
    alphaSlider->setGeometry(420, 370, 150, 20);
    alphaSlider->setMinimum(0);
    alphaSlider->setMaximum(1000);
    alphaLabel = new QLabel("Alpha", this);
    alphaLabel->setGeometry(580, 370, 150, 20);

    connect(alphaSlider, SIGNAL(valueChanged(int)), this, SLOT(opacityChange()));
    connect(normal, SIGNAL(clicked(bool)), this, SLOT(normalS()));
    connect(multiply, SIGNAL(clicked(bool)), this, SLOT(multiplyS()));
    connect(overlay, SIGNAL(clicked(bool)), this, SLOT(overlayS()));
    connect(darken, SIGNAL(clicked(bool)), this, SLOT(darkenS()));
    connect(lighten, SIGNAL(clicked(bool)), this, SLOT(lightenS()));
    connect(layer2, SIGNAL(stateChanged(int)), this, SLOT(layerSecondS()));
    connect(layer3, SIGNAL(stateChanged(int)), this, SLOT(layerThirdS()));

    r = 0; g = 0; b = 0;
    activeBtn = 1;
    alpha = 0.5;
    //alphaSlider->setValue(alpha * 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawImage(10, 10, img);
}

void MainWindow::opacityChange()
{
    alpha = alphaSlider->value();
    alpha = alpha/1000;
    backgroundPicture = picture1;
    if(layer2->isChecked() == 1){
        foregroundPicture = picture2;
    }
    if(layer3->isChecked() == 1){
        foregroundPicture = picture3;
    }
    if(activeBtn == 1){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = normalMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
        //putMode(colorForeground, colorForeground, normalMode);
    }
    else if(activeBtn == 2){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = multiplyMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
    }
    else if(activeBtn == 3){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = darkenMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
    }
    else if(activeBtn == 4){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = lightenMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
    }
    else if(activeBtn == 5){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = overlayMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
    }
    counter = 1;
    update();
}

void MainWindow::normalS()
{
    activeBtn = 1;
    counter = 1;
    backgroundPicture = picture1;
    if(layer2->isChecked() == 1){
        foregroundPicture = picture2;
    }
    if(layer3->isChecked() == 1){
        foregroundPicture = picture3;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            QColor colorBackground = backgroundPicture.pixel(i, j);
            QColor colorForeground = foregroundPicture.pixel(i, j);
            QColor newColor = normalMode(colorBackground, colorForeground);
            putPixelBlending_v2(i, j, newColor, newImg);
        }
    }
    AlphaBlending(backgroundPicture, newImg);
    QPainter p(&img);
    p.drawImage(0, 0, backgroundPicture);
    p.end();
    update();
}

void MainWindow::multiplyS()
{
    activeBtn = 2;
    counter = 1;
    backgroundPicture = picture1;
    if(layer2->isChecked() == 1){
        foregroundPicture = picture2;
    }
    if(layer3->isChecked() == 1){
        foregroundPicture = picture3;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            QColor colorBackground = backgroundPicture.pixel(i, j);
            QColor colorForeground = foregroundPicture.pixel(i, j);
            QColor newColor = multiplyMode(colorBackground, colorForeground);
            putPixelBlending_v2(i, j, newColor, newImg);
        }
    }
    AlphaBlending(backgroundPicture, newImg);
    QPainter p(&img);
    p.drawImage(0, 0, backgroundPicture);
    p.end();
    update();
}

void MainWindow::overlayS()
{
    activeBtn = 3;
    counter = 1;
    backgroundPicture = picture1;
    if(layer2->isChecked() == 1){
        foregroundPicture = picture2;
    }
    if(layer3->isChecked() == 1){
        foregroundPicture = picture3;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            QColor colorBackground = backgroundPicture.pixel(i, j);
            QColor colorForeground = foregroundPicture.pixel(i, j);
            QColor newColor = overlayMode(colorBackground, colorForeground);
            putPixelBlending_v2(i, j, newColor, newImg);
        }
    }
    AlphaBlending(backgroundPicture, newImg);
    QPainter p(&img);
    p.drawImage(0, 0, backgroundPicture);
    p.end();
    update();
}

void MainWindow::darkenS()
{
    activeBtn = 4;
    counter = 1;
    backgroundPicture = picture1;
    if(layer2->isChecked() == 1){
        foregroundPicture = picture2;
    }
    if(layer3->isChecked() == 1){
        foregroundPicture = picture3;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            QColor colorBackground = backgroundPicture.pixel(i, j);
            QColor colorForeground = foregroundPicture.pixel(i, j);
            QColor newColor = darkenMode(colorBackground, colorForeground);
            putPixelBlending_v2(i, j, newColor, newImg);
        }
    }
    AlphaBlending(backgroundPicture, newImg);
    QPainter p(&img);
    p.drawImage(0, 0, backgroundPicture);
    p.end();
    update();
}

void MainWindow::lightenS()
{
    activeBtn = 5;
    counter = 1;
    backgroundPicture = picture1;
    if(layer2->isChecked() == 1){
        foregroundPicture = picture2;
    }
    if(layer3->isChecked() == 1){
        foregroundPicture = picture3;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            QColor colorBackground = backgroundPicture.pixel(i, j);
            QColor colorForeground = foregroundPicture.pixel(i, j);
            QColor newColor = lightenMode(colorBackground, colorForeground);
            putPixelBlending_v2(i, j, newColor, newImg);
        }
    }
    AlphaBlending(backgroundPicture, newImg);
    QPainter p(&img);
    p.drawImage(0, 0, backgroundPicture);
    p.end();
    update();
}

void MainWindow::layerSecondS()
{
    if(layer2->isChecked() == 1){
        if(counter%2 == 0){
            backgroundPicture = picture1;
            foregroundPicture = picture2;
        }
        else foregroundPicture = picture2;
        counter++;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = normalMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
    }
}

void MainWindow::layerThirdS()
{
    if(layer3->isChecked() == 1){
        if(counter%2 == 0){
            backgroundPicture = picture1;
            foregroundPicture = picture3;
        }
        else foregroundPicture = picture3;
        counter++;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                QColor colorBackground = backgroundPicture.pixel(i, j);
                QColor colorForeground = foregroundPicture.pixel(i, j);
                QColor newColor = normalMode(colorBackground, colorForeground);
                putPixelBlending_v2(i, j, newColor, newImg);
            }
        }
        AlphaBlending(backgroundPicture, newImg);
        QPainter p(&img);
        p.drawImage(0, 0, backgroundPicture);
        p.end();
        update();
    }
}

void MainWindow::putPixelBlending_v2(int x, int y, QColor color, QImage &img)
{
    if(x >= 0 && x < width && y >= 0 && y < height){
        pix = img.scanLine(y);
        pix[x*4] = color.blue();
        pix[x*4 + 1] = color.green();
        pix[x*4 + 2] = color.red();
    }
}

void MainWindow::putPixelBlending(int x, int y, float alpha, QColor colorBackground, QColor colorForeground, QImage &img)
{
    if(x >= 0 && x < width && y >= 0 && y < height){
        pix = img.scanLine(y);
        pix[x*4] = alpha * colorForeground.blue() + (1 - alpha)*colorBackground.blue();
        pix[x*4 + 1] = alpha * colorForeground.green() + (1 - alpha)*colorBackground.green();
        pix[x*4 + 2] = alpha * colorForeground.red() + (1 - alpha)*colorBackground.red();
    }
}

void MainWindow::AlphaBlending(QImage background, QImage foreground)
{
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
             QColor colorBackground = background.pixel(i, j);
             QColor colorForeground = foreground.pixel(i, j);
             putPixelBlending(i, j, alpha, colorBackground, colorForeground, backgroundPicture);
         }
    }
}

QColor MainWindow::normalMode(QColor colorBackground, QColor colorForeground)
{
    return colorForeground;
}

QColor MainWindow::multiplyMode(QColor colorBackground, QColor colorForeground)
{
    QColor resultColor;
    resultColor.setBlue((colorBackground.blue() * colorForeground.blue()) >> 8);
    resultColor.setGreen((colorBackground.green() * colorForeground.green()) >> 8);
    resultColor.setRed((colorBackground.red() * colorForeground.red()) >> 8);
    return resultColor;
}

QColor MainWindow::overlayMode(QColor colorBackground, QColor colorForeground)
{
    QColor resultColor;
    if(colorBackground.blue() < 128){
        resultColor.setBlue((colorBackground.blue() * colorForeground.blue()) >> 7);
    }
    if(colorBackground.blue() >= 128){
        resultColor.setBlue(255 - ((255 - colorBackground.blue()) * (255 - colorForeground.blue()) >> 7));
    }
    if(colorBackground.green() < 128){
        resultColor.setGreen((colorBackground.green() * colorForeground.green()) >> 7);
    }
    if(colorBackground.green() >= 128){
        resultColor.setGreen(255 - ((255 - colorBackground.green()) * (255 - colorForeground.green()) >> 7));
    }
    if(colorBackground.red() < 128){
        resultColor.setRed((colorBackground.red() * colorForeground.red()) >> 7);
    }
    if(colorBackground.red() >= 128){
        resultColor.setRed(255 - ((255 - colorBackground.red()) * (255 - colorForeground.red()) >> 7));
    }
    return resultColor;
}

QColor MainWindow::darkenMode(QColor colorBackground, QColor colorForeground)
{
    QColor resultColor;
    if(colorBackground.blue() < colorForeground.blue()) resultColor.setBlue(colorBackground.blue());
    else resultColor.setBlue(colorForeground.blue());

    if(colorBackground.green() < colorForeground.green()) resultColor.setGreen(colorBackground.green());
    else resultColor.setGreen(colorForeground.green());

    if(colorBackground.red() < colorForeground.red()) resultColor.setRed(colorBackground.red());
    else resultColor.setRed(colorForeground.red());

    return resultColor;
}

QColor MainWindow::lightenMode(QColor colorBackground, QColor colorForeground)
{
    QColor resultColor;
    if(colorBackground.blue() > colorForeground.blue()) resultColor.setBlue(colorBackground.blue());
    else resultColor.setBlue(colorForeground.blue());

    if(colorBackground.green() > colorForeground.green()) resultColor.setGreen(colorBackground.green());
    else resultColor.setGreen(colorForeground.green());

    if(colorBackground.red() > colorForeground.red()) resultColor.setRed(colorBackground.red());
    else resultColor.setRed(colorForeground.red());

    return resultColor;
}


//----------------------------------------------------------------------------------------------------------------------
//void MainWindow::putMode(QColor colorBackground, QColor colorForeground, modeT mode){
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            colorBackground = backgroundPicture.pixel(i, j);
//            colorForeground = foregroundPicture.pixel(i, j);
//            QColor newColor = mode(colorBackground, colorForeground);
//            putPixelBlending_v2(i, j, newColor, newImg);
//        }
//    }
//    AlphaBlending(backgroundPicture, newImg);
//    QPainter p(&img);
//    p.drawImage(0, 0, backgroundPicture);
//    p.end();
//    update();
//}
