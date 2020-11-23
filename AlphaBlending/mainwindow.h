#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QLabel>
#include <QPainter>
#include <QGroupBox>
#include <QButtonGroup>

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
    QImage img, picture1, picture2, picture3;
    QImage backgroundPicture, foregroundPicture;
    QImage newImg;
    QPainterPath path;
    QLabel *alphaLabel;
    QButtonGroup *group_layerBtn, *group_modeBtn;
    QPushButton *normal, *multiply, *overlay, *darken, *lighten;
    QCheckBox *layer2, *layer3;
    //QColor colorBacground, colorForeground;
    int width, height;
    QSlider *alphaSlider;
    uchar *pix;
    int r, g, b;
    int counter;
    int activeBtn;
    float alpha;

    void putPixelBlending(int x, int y, float alpha, QColor colorBackground, QColor colorForeground, QImage &img);
    void putPixelBlending_v2(int x, int y, QColor color, QImage &img);
    void AlphaBlending(QImage background, QImage foreground);
    QColor normalMode(QColor colorBackground, QColor colorForeground);
    QColor multiplyMode(QColor colorBackground, QColor colorForeground);
    QColor overlayMode(QColor colorBackground, QColor colorForeground);
    QColor darkenMode(QColor colorBackground, QColor colorForeground);
    QColor lightenMode(QColor colorBackground, QColor colorForeground);
    typedef QColor (*modeT)(QColor, QColor);
    void putMode(QColor colorBackground, QColor colorForeground, modeT mode);
private slots:
    void paintEvent(QPaintEvent *);
    void opacityChange();
    void normalS();
    void multiplyS();
    void overlayS();
    void darkenS();
    void lightenS();
    void layerSecondS();
    void layerThirdS();
};

#endif // MAINWINDOW_H
