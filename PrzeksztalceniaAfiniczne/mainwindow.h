#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <armadillo>
#include <iostream>
#include <QImage>
#include <QPainter>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

using namespace arma;
using namespace std;

namespace Ui {
struct Point{
    int x;
    int y;
};
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
    vector<Ui::Point> listOfPoints;
    Ui::Point p;
    int width;
    int height;
    int r, g, b;
    uchar* pix;
    QImage img;
    QPushButton *translacja, *skalowanie;
    QLineEdit *CorX, *CorY;
    QLabel *x_text;
    QLabel *y_text;
    QLabel *text_translacja, *text_skalowanie, *text_rotacja;
    QSlider *translacjaTX, *translacjaTY, *skalowanieSX, *skalowanieSY, *rotacjaS;
    mat T, S, R, M;

    double tx, ty;
    double sx, sy;
    float alpha;
    double corx, cory;

    void putPixel(int x, int y);
    void drawSegment(int x1, int y1, int x2, int y2);
    void swap(int &x, int &y);
    void drawFigure(vector<Ui::Point> listOfPoints);
    void redrawFigure();
    //void vectorShift();
private slots:
    void paintEvent(QPaintEvent *);
    void gotCorX();
    void gotCorY();
    void translateBtn();
    void scaleBtn();
    void translationChange();
    void scaleChange();
    void rotationChange();
};

#endif // MAINWINDOW_H
