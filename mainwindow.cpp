#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedata.h"
#include "imgframe.h"
#include "mnistdataset.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ConfigureUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureUI() {
    this->ui->frame_3->is_editable_ = true;
    connect(ui->pushButton, SIGNAL(clicked()), ui->frame_3, SLOT(ClearFrame()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onRecognize()));
}

void MainWindow::onRecognize() {
    ;
    //MnistDataset data;
    //data.Load("train-images.idx3-ubyte", "train-labels.idx1-ubyte");
    //QImage test_image = data.Get(59999)->GetQImage();
    //this->ui->frame->SetImage(test_image);
}

void MainWindow::onLoadImages() {
    ;
}

void MainWindow::onLoadLabels() {
    ;
}
