#ifndef ANNRECOGNIZER_H
#define ANNRECOGNIZER_H
#include "floatfann.h"
#include "fann_cpp.h"
#include "mnistdataset.h"
#include <string>



class ANNRecognizer
{
public:
    ANNRecognizer();
    ~ANNRecognizer();
    bool SetTrainingData(MnistDataset* mnist);
    void ConstructANN(unsigned int num_layers, unsigned int* layers_capacity);
    void Train(unsigned int max_epochs, unsigned int epochs_between_report, float desired_error);
    bool LoadANN(const std::string config_file);
    void SaveANN(const std::string config_file);
    bool LoadTrain(const std::string train_file);
    void SaveTrain(const std::string train_file);
    bool IsAnnInit();
    bool IsTrainLoaded();
    void CancelTraining();
    unsigned char Recognize(ImageData &data);
    static int CallbackFunc(FANN::neural_net&,
                              FANN::training_data&,
                              unsigned int max_epochs,
                              unsigned int epochs_between_reports,
                              float desired_error, unsigned int epochs, void*);
    FANN::neural_net net;

private:
    bool is_ann_init_;
    bool is_train_loaded_;
    bool is_train_canceled_;
    static unsigned int FindMaxItem(float* array, unsigned int arr_len);
    FANN::training_data train_data_;
};

#endif // ANNRECOGNIZER_H
