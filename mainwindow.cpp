#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedata.h"
#include "imgframe.h"
#include "mnistdataset.h"


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
    image_data.Load(image);
    ImageData datacopy = image_data;
    ui->frame->SetImage(datacopy.getQImage());
}
