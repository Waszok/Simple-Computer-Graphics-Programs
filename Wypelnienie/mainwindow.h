#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QColorDialog>
#include <QPushButton>
#include <iostream>
#include <vector>
#include <stack>

namespace Ui {
class MainWindow;

struct Punkt{
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
    //QImage obr;
    QImage im;
    QColor bg;
    uchar *pix;

    int width;
    int height;
    QColor c;
    QPushButton *wybierz;


    //Metody
    void putPixel(int x, int y);
    //void flood_fill(int x, int y, Ui::Kolorek color);
    //void flood_fill_rec(int x, int y, Ui::Kolorek color, QColor bg);
    void drawCircle(int x0, int y0, double r);
    void flood_fill_2(int x, int y, QColor color);
public slots:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void wybierzKolor();
};
#endif // MAINWINDOW_H
