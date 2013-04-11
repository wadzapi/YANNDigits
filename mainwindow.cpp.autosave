#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedata.h"
#include "imgframe.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), ui->frame, SLOT(ClearFrame()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onRecognize()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRecognize() {
    QImage image(ui->frame->GetCroppedImage());
    ImageData image_data;
    int arr[6] = {10, 11, 12, 13, 14, 15};
    image_data.Load(arr, 6);
    ui->frame->SetImage(image_data.getQImage());
}
