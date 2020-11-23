#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QScrollBar>
#include <QPushButton>
#include <QLineEdit>
#include <iostream>
#include <vector>
#include <QPalette>
//#include <punkt.h>

namespace Ui {
class MainWindow;


struct Point{
    int x;
    int y;
};

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QScrollBar *slider;
    //QLineEdit *block1,*block2,*block3,*block4,*block5,*block6;
    std::vector<Ui::Point> moj;
    Ui::Point p, q;

    int licznik = 0;


private:
    Ui::MainWindow *ui;
    std::vector<Ui::Point>::iterator it;

    QPushButton *dodaj, *usun, *przesun;


    uint ld = 0;
    uint lu = 0;
    uint lp = 0;

    bool rysuj = 0;
    bool usun_zm = 0;
    bool przesun_zm = 0;

    QImage im;

    uchar* pix;
    int width;
    int height;
    unsigned int r, g, b;
    uint pom = 3;


    //Metody
    void putPixel(int x, int y);
    void drawBspline();
    void swap(int &x, int &y);
    void drawSegment(int x1, int y1, int x2, int y2);
    void drawControlPoint();

public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    //void mouseMoveEvent(QMouseEvent *);
    void dodajChanged();
    void usunChanged();
    void przesunChanged();
    void usuwanie();
    void przesuwanie();
};

#endif // MAINWINDOW_H
