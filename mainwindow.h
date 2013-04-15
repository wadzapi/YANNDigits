#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mnistdataset.h"

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
    void ConfigureUI();
    Ui::MainWindow *ui;
    MnistDataset mnist_;


public slots:
    void Recognize();
    void MnistImagesOpen();
    void MnistLabelsOpen();

};

#endif // MAINWINDOW_H
