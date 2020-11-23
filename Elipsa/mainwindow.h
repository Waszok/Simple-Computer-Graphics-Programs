#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QSlider>
#include <QLabel>
#include <QColor>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage im;
    QColor m_color;
    QSlider *slider;

    uchar* pix;
    int width;
    int height;

    //Punkty + punkty obrocone
    double x1;
    double y1;
    double obo1;
    double obo2;
    double obt1;
    double obt2;

    //Kat obrotu
    double beta=0;
    //Kolory
    int col1 = 1;
    int col2 = 2;

    int clickNumbers = 0;

    //Wspolrzedne punktow klikniecia
    double s1, s2, a1, a2, b1, b2;
    //Promienie elipsy
    int r1, r2;
    //Licznik klikniec
    int licznik = 0;
    //Tablica pomocnicza przechowujaca kolory
    int tab[6];

    unsigned int re1, ge1, be1, re2, ge2, be2;
    unsigned int r, g, b;

    //Metody
    void putPixel(int x, int y);
    void drawElipse(int s1, int s2, int r1, int r2);
    void swap(double &x, double &y);
    void drawSegment(double x1, double y1, double x2, double y2, int zm);

private slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void obrot(int a);
    void onColorChanged();
};

#endif // MAINWINDOW_H
