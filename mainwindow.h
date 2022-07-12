#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QDebug>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getChangedColor(int valueColor, int shift);
    void settingFieldStyle();
    void showGameField();
    void defineGoalColor();
    void defineSquaresColors();
    void defineCalibratedColors();
    void showSquares();
    void showAveragedColorSquare();
    void showCalibratedSquares();
    void defineRandShiftKoef();
    void rgb(QColor color);
    void calibreColumn(int colIdx);
    void calibreColors(QList<int> calibredColIdxs, QString colComponent, int calibreValue);
    void closestColorsDetecting();
    void averagedColor();
    void closestColor();
    int closestColorForColumn(int colIdx);
    QString getColorComponent(int colIdx);
    QMap<QString, int> getCalibredColComponent(int colIdx);
    QList<int> getColorIdxs(int colIdx);

    int getValue(int colIdx);
    float distance(QColor color);

private slots:
    void on_btnApply_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsRectItem *rectangle1;
    QGraphicsRectItem *rectangle2;
    QGraphicsRectItem *rectangle3;
    QGraphicsRectItem *rectangle4;
    QGraphicsRectItem *rectangle5;
    QGraphicsRectItem *rectangle6;
    QGraphicsRectItem *rectangle7;
    QGraphicsRectItem *rectangle8;
    QGraphicsRectItem *rectangle9;
    QGraphicsRectItem *rectangle_r;
    QGraphicsRectItem *rectangle_c;

    QPen *squarePen;
    QColor *goalColor;
    QColor *m_averagedColor;
    QList<int> *randShiftKoef;
    QList<QColor> *shiftedColors;
    QList<QColor> *calibratedColors;
    QList<int> calibredColIdxs;
    QList<int> closestColorIdxs;
    int rand1;
    int rand2;
    int rand3;
};
#endif // MAINWINDOW_H
