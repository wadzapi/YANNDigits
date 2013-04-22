#ifndef ANNRECOGNIZER_H
#define ANNRECOGNIZER_H
////#include "fann.h"
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
    void PrintParameters();
    void Train(unsigned int max_epochs, unsigned int epochs_between_report, float desired_error);
    bool Load(const std::string config_file);
    void Save(const std::string config_file);
    FANN::neural_net net;
    bool IsInit();
    unsigned char Recognize(ImageData& data);


private:
    FANN::training_data train_data_;
    unsigned int num_layers_;
    unsigned int num_input_;
    unsigned int num_output_;
    unsigned int mnist_count_;
    void DeleteInputData();
    bool is_ann_init_;
    bool is_train_loaded_;
    static unsigned int FindMaxItem(float* array, unsigned int arr_len);

};

#endif // ANNRECOGNIZER_H
