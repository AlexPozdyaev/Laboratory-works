/* 10.	Создать приложение, которое считывает матрицу из файла и с помощью вкладок представляет ее в двух видах:
  первый – исходный вид матрицы,
  второй – в котором каждый элемент уменьшен на значение минимального элемента в текущей строке матрицы. */



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>//Обеспечивает использование кириллицы
#include <QFileDialog>//Обеспечивает работу с файлами
#include <QDebug>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    row = 0,  col = 0;//Обнуляем кол-во строк и стобцов
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Swap(QTableWidget* table2, int row, int col, int i, int nuMin)
{
    double min = table2->item(i, nuMin)->text().toDouble();
    qDebug() << "Происходит вставка";
    for(int per = 0; per < col; per++)
    {
        double save = table2->item(i, per)->text().toDouble() - min;//Элемент который = текущий элемент - минимальный элемент в строке
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(save));
        item->setTextAlignment(Qt::AlignCenter);//Выравниваем элемент таблицы
        table2->setItem(i, per, item);//Вставляем элемент в таблицу
    }
}

void MainWindow::on_OpenFile_triggered()
{
    QString name = QFileDialog::getOpenFileName(this, "Открыть", "E:/Travova 2.1/Pozdyaev_2_10/Test.txt",
                                                QString("Текстовые файлы(*.txt);;Все файлы(*)"));//Считываем имя файла
    ui->label->text().clear();// Очистка
    QFile file(name);//Создаем файл и присваиваем ему имя
    file.open(QIODevice::ReadOnly);//Открываем файл для чтения
    QString str;//Переменная для хранения одной строки(матрицы) из файла
    QStringList list;//Создаем список, чтобы отделить числа в строке
    ui->tabWidget->setCurrentIndex(1);//Переходим на 2(1) вкладку
    table1 = new QTableWidget(row,  col, ui->tab);//Создаем QTableWidget, в качестве родительского окна указываем первую вкладку(размер (0,0))
    table1->resize(ui->tab->size());//Подгоняем размеры table1 под размеры первой вкладки
    table1->horizontalHeader()->setDefaultSectionSize(50);//Ширина столбцов
    while(!file.atEnd())//Пока не закончится файл
    {
        str = file.readLine();//Считываем строку
        table1->insertRow(row);//Добавляем строку в table1
        list = str.split(QRegExp("\\s+"), QString::SkipEmptyParts);//Делим строку на слова(числа)
        for (int i = 0; i < list.size(); ++i)//Проходимся по списку чисел(строки)
        {
            if (row==0) table1->insertColumn(i);//Если строка первая, значит надо добавлять столбцы
            QTableWidgetItem* item = new QTableWidgetItem(QString(list[i]));//Создаем элемент таблицы
            item->setTextAlignment(Qt::AlignCenter);//Выравниваем элемент таблицы
            table1->setItem(row, i, item);//Вставляем элемент в таблицу

        }
        row++;//Увеличиваем кол-во строк
    }
    qDebug() << "Считывание";
    col = table1->columnCount();//Выясняем сколько столбцов получилось
    ui->tabWidget->setCurrentIndex(0);//Переходим на 1(0) вкладку

    table2 = new QTableWidget(row, col,ui->tab_2);//Создаем QTableWidget, в качестве родительского окна указываем вторую вкладку
    table2->resize(ui->tab_2->size());//Подгоняем размеры table2 под размеры первой вкладки
    table2->horizontalHeader()->setDefaultSectionSize(50);//Ширина столбцов
    for(int i = 0; i < row; i++)//Переносим нашу матрицу во вторую вкладку
    {
        for(int j = 0; j <  col; j++)
        {
            double num = table1->item(i,j)->text().toDouble();
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(num));
            item->setTextAlignment(Qt::AlignCenter);//Выравниваем элемент таблицы
            table2->setItem(i, j, item);//Вставляем элемент в таблицу
        }
    }
    int nuMin = 0;//Номер максимального элемента
    for (int i = 0; i < row; i++)
    {
        double num = table2->item(i,0)->text().toDouble();
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(num));
        double min = table2->item(i,0)->text().toDouble();//Временное число из строки
        nuMin = 0;
        for(int j = 0; j < col; j++)//Идём по столбцам
        {
            double tmp = table2->item(i,j)->text().toDouble();//Временное число из i строки и j столбца
            if(min > tmp)//Если найдено число меньше
            {
                qDebug() << j;
                nuMin = j;
            }
        }
        Swap(table2, row, col, i ,nuMin);
    }
}

