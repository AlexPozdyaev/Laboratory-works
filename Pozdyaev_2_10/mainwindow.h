#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtWidgets"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int row, col;
    QTableWidget *table1, *table2;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     //bool fg;


private slots:
    void on_OpenFile_triggered();

public slots:
    void Swap(QTableWidget* table2, int row, int col, int i, int nuMin);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
