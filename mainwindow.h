#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mnistdataset.h"
#include "counter.h"

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
    void initCounter();
    void LoadMnistImage(unsigned int index);
    void LoadMnistLabel(unsigned int index);
    Ui::MainWindow *ui;
    MnistDataset mnist_;
    Counter images_counter_;
    Counter labels_counter_;



public slots:
    void Recognize();
    void NextMnist();
    void PrevMnist();
    void MnistImagesOpen();
    void MnistLabelsOpen();

};

#endif // MAINWINDOW_H
