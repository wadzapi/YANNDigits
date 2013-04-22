#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "counter.h"
#include "mnistdataset.h"
#include "annrecognizer.h"
#include <QTableWidgetItem>


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
    Counter images_counter_;
    Counter labels_counter_;
    MnistDataset mnist_;
    ANNRecognizer ann_;
    void SetActivationFunc();
    void SetErrorFunc();




public slots:
    void Recognize();
    void NextMnist();
    void PrevMnist();
    void MnistImagesOpen();
    void MnistLabelsOpen();
    void AdjustTableRows(int num_layers);
    void CreateANN();
    void LoadANN();
    void SaveANN();
    void StartTraining();


};

#endif // MAINWINDOW_H
