#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(770, 390);
    scene->setSceneRect(0, 0, 760, 380);
    QPen *squarePen2 = new QPen;
    squarePen2->setColor(Qt::black);

    settingFieldStyle();

    showGameField();
    qInfo() << "it is shown3";

}

void MainWindow::settingFieldStyle()
{
    squarePen = new QPen;
    squarePen->setColor(Qt::black);
    squarePen->setWidth(2);
}

int MainWindow::getChangedColor(int valueColor, int shift)
{
    int valueShifted = valueColor + shift;
    if (valueShifted > 255)
    {
        valueShifted = valueShifted - 255;
    }
    return valueShifted;
}

void MainWindow::defineGoalColor()
{
    int valueR = QRandomGenerator::global()->bounded(0, 255);
    int valueB = QRandomGenerator::global()->bounded(0, 255);
    int valueG = QRandomGenerator::global()->bounded(0, 255);
    qInfo() << "goal color: "<< "red " << valueR << "green " << valueG << "blue " << valueB ;
    goalColor = new QColor(valueR, valueG, valueB, 255);

}

void MainWindow::defineSquaresColors()
{
    defineRandShiftKoef();
    int shiftedColor;
    int redGoalColorComp = goalColor->red();
    int greenGoalColorComp = goalColor->green();
    int blueGoalColorComp = goalColor->blue();
    shiftedColors = new QList<QColor>;
    foreach(int shift, *randShiftKoef)
    {
        shiftedColor = getChangedColor(redGoalColorComp, shift);
        shiftedColors->append(QColor(shiftedColor, greenGoalColorComp, blueGoalColorComp, 255));

        shiftedColor = getChangedColor(greenGoalColorComp, shift);
        shiftedColors->append(QColor(redGoalColorComp, shiftedColor, blueGoalColorComp, 255));

        shiftedColor = getChangedColor(blueGoalColorComp, shift);
        shiftedColors->append(QColor(redGoalColorComp, greenGoalColorComp, shiftedColor, 255));

    }
    std::shuffle(shiftedColors->begin(), shiftedColors->end(), std::random_device());

    foreach (QColor color, *shiftedColors)
    {
        rgb(color);
    }
}

void MainWindow::rgb(QColor color)
{
    qInfo() << "red " << color.red() << "green " << color.green() << "blue " << color.blue();
    //qInfo() << "redF " << color.redF() << "greenF " << color.greenF() << "blueF " << color.blueF();
}

void MainWindow::defineRandShiftKoef()
{
    int rand,krand;
    int randM = 51;
    randShiftKoef = new QList<int>;
    for (int i=0;i<3;i++)
    {
        krand = QRandomGenerator::global()->bounded(2, 4);
        qInfo() << "krand " << krand;
        rand = QRandomGenerator::global()->bounded(randM-1, krand*randM);
        randShiftKoef->append(rand);
        qInfo() <<"rand "<< rand;
    }
}

void MainWindow::showSquares()
{
    int startX = 110;
    int startY = 10;
    int x, y;
    QColor color;
    int colorIndex = 0;
    for (int  xIdx = 0; xIdx<3; xIdx++)
    {
        for (int  yIdx = 0; yIdx<3; yIdx++)
        {
            //qInfo() <<"colorIndex "<< colorIndex;
            color = shiftedColors->at(colorIndex);
            colorIndex += 1;
            QBrush brushShifted(color);
            x = startX + 100 * xIdx;
            y = startY + 100 * yIdx;
            scene->addRect(x, y, 100, 100, *squarePen, brushShifted);
        }
    }
    QBrush brushR(*goalColor);
    rectangle_r = scene->addRect(5, 50, 100, 100, *squarePen, brushR);
    rectangle_c = scene->addRect(5, 180, 100, 100, *squarePen, brushR);

}

void MainWindow::showAveragedColorSquare()
{
    QBrush brushR(*m_averagedColor);
    qInfo() <<"goalColor ";
    rgb(*goalColor);
    qInfo() <<"showAveragedColorSquare ";
    rgb(*m_averagedColor);
    rectangle_c = scene->addRect(5, 180, 100, 100, *squarePen, brushR);
}

void MainWindow::showCalibratedSquares()
{
    //qInfo() << shiftedColors;
    //qInfo() << calibratedColors;
    int startX = 415;
    int startY = 10;
    int x, y;
    QColor colorC;
    int colorIndex = 0;
    for (int  xIdx = 0; xIdx<3; xIdx++)
    {
        for (int  yIdx = 0; yIdx<3; yIdx++)
        {
            //qInfo() <<"colorIndex "<< colorIndex;
            colorC = calibratedColors->at(colorIndex);
            colorIndex += 1;
            QBrush brushCalibrated(colorC);
            x = startX + 100 * xIdx;
            y = startY + 100 * yIdx;
            scene->addRect(x, y, 100, 100, *squarePen, brushCalibrated);
        }
    }
}

void MainWindow::showGameField()
{
    defineGoalColor();

    defineSquaresColors();

    showSquares();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::defineCalibratedColors()
{
    calibratedColors = new QList(*shiftedColors);
    for (int  colIdx = 0; colIdx<3; colIdx++)
    {
       calibreColumn(colIdx);
    }
}

void MainWindow::calibreColumn(int colIdx)
{
     QList<int> calibredColIdxs = getColorIdxs(colIdx);
     QString colComponent = getColorComponent(colIdx);
     int calibrValue = getValue(colIdx);
     calibreColors(calibredColIdxs, colComponent, calibrValue);
}

QList<int> MainWindow::getColorIdxs(int colIdx)
{
    QList<int> colorIdxs;
    if (colIdx==0)
    {
        colorIdxs.append(0);
        colorIdxs.append(1);
        colorIdxs.append(2);
    }
    if (colIdx==1)
    {
        colorIdxs.append(3);
        colorIdxs.append(4);
        colorIdxs.append(5);
    }
    if (colIdx==2)
    {
        colorIdxs.append(6);
        colorIdxs.append(7);
        colorIdxs.append(8);
    }
     return colorIdxs;
}

QString MainWindow::getColorComponent(int colIdx)
{
    QString colorQString;
    if (colIdx==0)
    {
        if (ui->redCol1->isChecked())
        {
            colorQString = "red";
        }
        if (ui->greenCol1->isChecked())
        {
            colorQString = "green";
        }
        if (ui->blueCol1->isChecked())
        {
            colorQString = "blue";
        }
    }
    if (colIdx==1)
    {
        if (ui->redCol2->isChecked())
        {
            colorQString = "red";
        }
        if (ui->greenCol2->isChecked())
        {
            colorQString = "green";
        }
        if (ui->blueCol2->isChecked())
        {
            colorQString = "blue";
        }
    }
    if (colIdx==2)
    {
        if (ui->redCol3->isChecked())
        {
            colorQString = "red";
        }
        if (ui->greenCol3->isChecked())
        {
            colorQString = "green";
        }
        if (ui->blueCol3->isChecked())
        {
            colorQString = "blue";
        }
    }
    //qInfo() <<"colIdx  "<< colIdx << " cc "<<colorQString;
    return colorQString;
}


int MainWindow::getValue(int colIdx)
{
     int calibreValue;
     if (colIdx==0)
     {
         calibreValue = ui->lEdCol1->text().toInt();
     }
     if (colIdx==1)
     {
         calibreValue = ui->lEdCol2->text().toInt();
     }
     if (colIdx==2)
     {
         calibreValue = ui->lEdCol3->text().toInt();
     }
     //qInfo() <<"colIdx  "<< colIdx << " vv "<<calibreValue;
     return calibreValue;
}

void MainWindow::calibreColors(QList<int> calibredColIdxs, QString colComponent, int calibreValue)
{
     QColor calibratedColor;
     foreach (int idx, calibredColIdxs)
     {
         calibratedColor = calibratedColors->at(idx);
         if (colComponent == "red")
         {
            //qInfo() << "redred " << idx << " val " <<calibreValue << " col "<< getChangedColor(calibratedColor.red(), calibreValue);
            //rgb(calibratedColor);
            calibratedColor.setRed(getChangedColor(calibratedColor.red(), calibreValue));
            //rgb(calibratedColor);
         }
         if (colComponent == "green")
         {
            //qInfo() << "greengreen " <<calibreValue << " col "<< getChangedColor(calibratedColor.green(), calibreValue);
            //rgb(calibratedColor);
            calibratedColor.setGreen(getChangedColor(calibratedColor.green(), calibreValue));
            //rgb(calibratedColor);
          }
         if (colComponent == "blue")
          {
            //qInfo() << "blueblue " <<calibreValue << " col "<< getChangedColor(calibratedColor.blue(), calibreValue);
            //rgb(calibratedColor);
            calibratedColor.setBlue(getChangedColor(calibratedColor.blue(), calibreValue));
            //rgb(calibratedColor);
          }
         calibratedColors->replace(idx, calibratedColor);
         qInfo() << "calibratedColors q " << calibratedColors->size();
     }
}

void MainWindow:: closestColorsDetecting()
{
    //QList<int> closestColorIdxs;
    closestColorIdxs.clear();
    for (int  colIdx = 0; colIdx<3; colIdx++)
    {
        closestColorIdxs.append(closestColorForColumn(colIdx));
    }
    qInfo() << "closestColorIdxs s " << closestColorIdxs.size();
    qInfo() << "closestColorIdxs l " << closestColorIdxs.length();
}

void MainWindow:: averagedColor()
{
    float averagedRedF=0,averagedGreenF=0,averagedBlueF=0;
    int averagedRed=0,averagedGreen=0,averagedBlue=0;
    foreach (int colorIdx, closestColorIdxs)
    {
        averagedRedF = averagedRedF + calibratedColors->at(colorIdx).redF();
        averagedGreenF = averagedGreenF + calibratedColors->at(colorIdx).greenF();
        averagedBlueF = averagedBlueF + calibratedColors->at(colorIdx).blueF();
        qInfo() << "FFF" << "averagedRedF " << averagedRedF << "averagedGreenF " << averagedGreenF << "averagedBlueF " << averagedBlueF;
    }
    averagedRedF = averagedRedF/3;
    averagedGreenF = averagedGreenF/3;
    averagedBlueF = averagedBlueF/3;

    averagedRed = round(averagedRedF*255);
    averagedGreen = round(averagedGreenF*255);
    averagedBlue = round(averagedBlueF*255);

    qInfo() << "averagedRed " << averagedRed << "averagedGreen " << averagedGreen << "averagedBlue " << averagedBlue;
    m_averagedColor = new QColor(averagedRed, averagedGreen, averagedBlue, 255);
}

int MainWindow:: closestColorForColumn(int colIdx)
{
    int current_inx;
    float lowest_dist = 4;
    float dist;
    QList<int> colorIdxs;
    QColor color;
    colorIdxs = getColorIdxs(colIdx);
    foreach (int  colorIdx, colorIdxs)
    {
        color = calibratedColors->at(colorIdx);
        qInfo() << "goal ";
        rgb(*goalColor);
        qInfo() << "redF " << goalColor->redF() << "greenF " << goalColor->greenF() << "blueF " << goalColor->blueF();
        rgb(color);
        qInfo() << "redF " << color.redF() << "greenF " << color.greenF() << "blueF " << color.blueF();
        qInfo() << "colorHue " << color.hueF() << "saturation " << color.saturationF() << "lithness " << color.lightnessF();
        dist = distance(color);
        if (dist<lowest_dist) {
            lowest_dist = dist;
            current_inx = colorIdx;
        }
        qInfo() << "dist: " << dist;
    }
    return current_inx;
}

void MainWindow:: closestColor()
{
    int current_inx;
    float lowest_dist = 4;
    float dist;
    QColor clColor;
    QList<int> colorIdxs;
    foreach (QColor  color, *calibratedColors)
    {
        qInfo() << "goal ";
        rgb(*goalColor);
        qInfo() << "redF " << goalColor->redF() << "greenF " << goalColor->greenF() << "blueF " << goalColor->blueF();
        rgb(color);
        qInfo() << "redF " << color.redF() << "greenF " << color.greenF() << "blueF " << color.blueF();
        qInfo() << "colorHue " << color.hueF() << "saturation " << color.saturationF() << "lithness " << color.lightnessF();
        dist = distance(color);
        if (dist<lowest_dist) {
            lowest_dist = dist;
            clColor = color;
        }
        qInfo() << "dist: " << dist;
    }
    qInfo() <<"OO clColor "<< clColor;
    *m_averagedColor = clColor;
    rgb(*m_averagedColor);
}

float MainWindow:: distance(QColor color)
{
    float dist;
    float koef1=1.0;
    float koef2=1.0;
    float koef3=1.0;
    float koef4=0.6;
    float koef5=0.3;
    float koef6=0.1;
    float rrr = color.redF()-goalColor->redF();
    qInfo() << "c redF: " << color.redF() << "g redF: " << goalColor->redF() << "red rrr: " << rrr;
    float d1=abs(color.redF()-goalColor->redF())*koef1;
    float d2=abs(color.greenF()-goalColor->greenF())*koef2;
    float d3=abs(color.blueF()-goalColor->blueF())*koef3;
    float d4=abs(color.hueF()-goalColor->hueF())*koef4;
    float d5=abs(color.saturationF()-goalColor->saturationF())*koef5;
    float d6=abs(color.lightnessF()-goalColor->lightnessF())*koef6;
    qInfo() << "d1: " << d1 << "d2: " << d2 << "d3: " << d3 << "d4: " << d4 << "d5: " << d5 << "d6: " << d6;
    dist = (d1+d2+d3+d4+d5+d6)/6;
    return dist;
}


void MainWindow::on_btnApply_clicked()
{
    qInfo() << "apply -------------------------------------";
    defineCalibratedColors();
    showCalibratedSquares();
    closestColorsDetecting();
    averagedColor();
    showAveragedColorSquare();
    closestColor();
    //showAveragedColorSquare();
}

