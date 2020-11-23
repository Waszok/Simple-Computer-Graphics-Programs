#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <iostream>
#include <vector>
#include <QColorDialog>
#include <QColor>
#include <QLineEdit>
#include <QLabel>
#include <QFont>

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

private:
    Ui::MainWindow *ui;

    QImage im;
    QImage imKopia;
    QPixmap pixmap1;
    QPainterPath path;
    QRectF target; // prostokąt docelowy
    QRectF source; // prostokąt wyciąganego fragmentu grafiki
    uchar* pix;
    QPushButton *wybierz;
    QPushButton *czysc;
    QPushButton *ok;
    QPushButton *erozja;
    QPushButton *dylatacja;
    QPushButton *otwarcie;
    QPushButton *domkniecie;
    QLineEdit *x_wsp;
    QLineEdit *y_wsp;
    QLabel *x_text;
    QLabel *y_text;
    QLabel *text;
    QColor c;
    Ui::Point p;

    std::vector<Ui::Point> moj;
    std::vector<double> tablica_pp;
    std::vector<Ui::Point> tab_pom;

    int width;
    int height;
    int czy_juz_jest = 0;
    double wsp, x;
    int ymin;
    int ymax;

    //Metody
    void putPixel(int x, int y);
    void scanLines();
    void swap(int &x, int &y);
    void drawHorizontalLine(double x1, double x2, double y);
    void findMinMax();
    void drawSegment(int x1, int y1, int x2, int y2);
    void dylatacja_function();
    void erozja_function();
    void otwarcie_function();
    void domkniecie_function();

public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wybierzKolor();
    void czyscEkran();
    void dodanoX();
    void dodanoY();
    void potwierdz();
    void pressErozja();
    void pressDylatacja();
    void pressOtwarcie();
    void pressDomkniecie();
};

#endif // MAINWINDOW_H
