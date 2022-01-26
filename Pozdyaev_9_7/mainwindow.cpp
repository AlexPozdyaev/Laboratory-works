#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pole.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec*codec = QTextCodec::codecForName("UTF-8");
 // QTextCodec::setCodecForCStrings(codec);
    QScrollArea*scroll=new QScrollArea(this);
    Pole*pole=new Pole(scroll);  // создаем новый виджет
    scroll->setWidget(pole);  // размещаем виджет в области прокрутки
    setCentralWidget(scroll);  // делаем область прокрутки рабочей областью окна
    connect(ui->actionOpen,SIGNAL(triggered()),pole,SLOT(fileOpen()));
    // связываем вызов команды File|Open со слотом, который мы создадим в классе Pole
}

MainWindow::~MainWindow()
{
    delete ui;
}
