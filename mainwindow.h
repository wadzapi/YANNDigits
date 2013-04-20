#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mnistdataset.h"
#include "counter.h"
#include "annrecognizer.h"

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
    void LoadMnistImage();
    void LoadMnistLabel();
    Ui::MainWindow *ui;
    MnistDataset mnist_;
    Counter images_counter_;
    Counter labels_counter_;
    ANNRecognizer ann_;



public slots:
    void Recognize();
    void NextMnist();
    void PrevMnist();
    void MnistImagesOpen();
    void MnistLabelsOpen();
    void AdjustTableRows(int numLayers);
};

#endif // MAINWINDOW_H
