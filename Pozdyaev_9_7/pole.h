#ifndef POLE_H

#define POLE_H

#include <QWidget>
#include <QtWidgets>
#include <QtGui>

class Pole : public QWidget

{

Q_OBJECT

public:

explicit Pole(QScrollArea* parent = 0);

// измените тип указателя на родительское окно

QScrollArea* Parent; // указатель на область прокрутки

void paintEvent(QPaintEvent *); // перерисовывает содержимое окна

QFile file; // файл, содержащий массив

QString fileName; // имя файла

QVector<double> v; // массив

QVector<double> copyV; // копия массива

QVector<double> copyP; // копия массива

QFont font; // шрифт

int dy; // расстояние между элементами массива при выводе на экран

int k; // количество элементов массива

void Pie(QPainter&, QRect&, int, int, int);

// рисует один кусок диаграммы

signals:

public slots:

void fileOpen(); // слот, считывающий массив из файла

};

#endif // POLE_H
