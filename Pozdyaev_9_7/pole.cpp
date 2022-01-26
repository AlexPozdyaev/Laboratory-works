#include "pole.h"
#include "mainwindow.h"
#include "QPainter"
#include "QFile"

Pole::Pole(QScrollArea*parent):   // измените тип указателя на родительское окно
QWidget(parent)
{
    Parent=parent; // запоминаем значение указателя
}
void Pole::paintEvent(QPaintEvent*) // отображаем массив на экране:
{
    QPainter painter(this);
    int y=20; // уровень, с которого начинается вывод массива на экран
    painter.setFont(font); // устанавливаем шрифт
    //Вывод массива:
    double sum=0; // сумма элементов массива
    k=v.size(); // размер массива
    for(int i=0;i<k;++i) // проходим по массиву
    {
        painter.drawText(10,y,QString::number(v[i]));
        // выводим очередной элемент массива на экран
        y+=dy;     // переходим на другую строку
        sum+=v[i]; // добавляем элемент к сумме
    }
    copyV=v;
    copyP=v;
    // копируем массив, чтобы исходный массив отображался на экране без изменений
    qSort(copyV.begin(),copyV.end(),qGreater<double>());
    painter.drawText(10,y,"Исправленный по заданию массив:");
    y+=dy;
    int max = -1,a = 0, num = -1;

    for(int i=0;i<k;++i) // проходим по массиву
    {
        if (max < copyP[i])
        {max = copyP[i];
         num = i;
        }
    }

    if (num >=0)
    { a = copyP[num];
      copyP[num] = copyP[k-1];
      copyP[k-1] = a;
    }

    for(int i=0;i<k;++i)
    {
        painter.drawText(10,y,QString::number(copyP[i]));
            // выводим очередной элемент массива на экран
        y+=dy;     // переходим на другую строку
    }

    // сортируем копию массива по убыванию, чтобы построить диаграмму
    painter.drawText(10,y,"Отсортированный массив:");
    y+=dy;
    int z = 0,amount = 0, r = 0;
    double b = copyV[0], B;
    QFile fileOut("out.txt");
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);

    if (!fileOut.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
    }

    QTextStream t(&fileOut);

    for(int i=0;i<k;++i) // проходим по массиву
    {
        t << copyV[i] << "\n";
        if(copyV[i] == b)
        {
            z++;
        }
        else
        {
            r += z;
            b = copyV[r];
            if(z > amount)
            {
                amount = z;
                B = copyV[r-1];
            }
            z = 1;
        }

        painter.drawText(10,y,QString::number(copyV[i]));
        // выводим очередной элемент массива на экран
        y+=dy;     // переходим на другую строку
    }

    //Диаграмма:
    QRect rectBase=Parent->rect();
    // прямоугольник, соответствующий видимой части области прокрутки
    QRect rect=rectBase; // прямоугольник, в котором мы будем рисовать диаграмму
    int h=rectBase.height()-25; // несколько уменьшим высоту прямоугольника
    rect.setSize(QSize(h,h)); // задаем квадрат высотой h
    rect.moveRight(rectBase.width()-25); // перемещаем квадрат к правой границе окна
    double startAngle=0; // начальный угол для первого фрагмента диаграммы
    double spanAngle=0; // угол,
    for(int i=0;i<qMin(13,k);++i) //
    {
        spanAngle=360*16.*copyV[i]/sum;//Уголмеждурадиусами
        Pie(painter,rect,startAngle,spanAngle,i);
        // рисуем сектор с помощью функции, определенной ниже
        startAngle+=spanAngle; // переходим к следующему сектору
    }
    if(k>13) // отображаем остальные элементы массива в сумме:
    {
        spanAngle=360*16-startAngle; // определяем размер соответствующего угла
        Pie(painter,rect,startAngle,spanAngle,13);
        // рисуем оставшуюся часть диаграммы
    }
}
void Pole::fileOpen()
{
    if(file.isOpen())file.close();
    v.clear(); // удаляем ранее считанный массив
    copyV.clear(); // и его копию
    fileName=QFileDialog::getOpenFileName(this,"Открыть файл",QString(),
    QString("Текстовые файлы(*.txt);;Все файлы(*.*)"));
    // считываем имя файла с помощью специального окна
    if(!fileName.isEmpty()) // если имя файла выбрано
    {
        file.setFileName(fileName);
        // связываем объект файл с физическим файлом на диске
        file.open(QIODevice::ReadOnly); // открываем файл
        QTextStream in(&file); // создаем поток для работы с файлами
        double x; // одно число из файла
        while(true) // как бы бесконечный цикл для чтения данных из файла
        {
            in>>x; // считываем одно число
            if(x<0) // если число недопустимо
            {
                QMessageBox::critical(this,"Ошибка в данных",
                "Все числа должны быть больше 0");
                return;
            }
            if(!in.atEnd()) // если файл не закончен
            {
                v<<x; // записываем число
            }
            else break; //
        }
        font=QFont("Serif",12);
        QFontMetrics fm(font);
        dy=fm.height();
        k=v.size();
        int height=qMax(1500,20+k*dy);
        this->resize(2000,height);
    }
}
void Pole::Pie(QPainter&painter,QRect&rect,int startAngle,int spanAngle,int i)
{
    int c=i+1;
    int I,R,G,B;
    B=c%2;c/=2;
    G=c%2;c/=2;
    R=c%2;c/=2;
    I=c%2;
    painter.setBrush(QBrush(QColor(I*100+R*155,I*100+G*155,I*100+B*155))); //
    painter.drawPie(rect,startAngle,spanAngle); //
}

