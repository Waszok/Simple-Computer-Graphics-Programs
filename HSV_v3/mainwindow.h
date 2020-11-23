#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MIN(a,b,c) ((a)<(b)?(a):(b))<(c)?(((a)<(b)?(a):(b))):(c)
#define MAX(a,b,c) ((a)>(b)?(a):(b))>(c)?(((a)>(b)?(a):(b))):(c)

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QSlider>
#include <QFormLayout>
#include <QLabel>
#include <QColor>
#include <iostream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QImage img, img2;
    int width;
    int height;
    float R, G, B, hue, sat, val;
    QColor HSV;
    //QPainter painter;
    //uchar *pix;

    QWidget *suwaki;
    QFormLayout *slideryLayout;
    QLabel *labelR;
    QLabel *labelG;
    QLabel *labelB;
    QLabel *labelH;
    QLabel *labelS;
    QLabel *labelV;
    QSlider *sliderR;
    QSlider *sliderG;
    QSlider *sliderB;
    QSlider *sliderH;
    QSlider *sliderS;
    QSlider *sliderV;

    void putPixel(int x, int y, int r, int g, int b, QImage &im);
    void rgb2hsv(float r, float g, float b);
    void hsv2rgb(float hue, float sat, float val);
    void drawH();
    void drawSV();
    void drawHorizontalLine(int y, int x1, int x2);
    void drawHorizontalLineOn(int y, int x1, int x2);
    void drawCircle(int x0, int y0);

private slots:
    void paintEvent(QPaintEvent *);

    void zmianaRGB();
    void zmianaHSV();
};

#endif // MAINWINDOW_H
