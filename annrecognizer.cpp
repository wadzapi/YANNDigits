#include "annrecognizer.h"
#include <cstdlib>

#include <iostream>
#include <iomanip>

ANNRecognizer::ANNRecognizer() :
    is_ann_init_(false),
    is_train_loaded_(false),
    is_train_canceled_(false)
{

}

ANNRecognizer::~ANNRecognizer() {
}

void ANNRecognizer::ConstructANN(unsigned int num_layers, unsigned int* layers_capacity) {
    net.create_standard_array(num_layers, layers_capacity);
    net.set_callback(&CallbackFunc, NULL);
    ///установка стандартных значений параметров
    net.set_learning_rate(0.7f);
    net.set_activation_steepness_hidden(1.0);
    net.set_activation_steepness_output(1.0);
    net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
    net.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);
    is_ann_init_ = true;
}



bool ANNRecognizer::SetTrainingData(MnistDataset *mnist) {
    if (is_train_loaded_) {
        train_data_.destroy_train();
        is_train_loaded_ = false;
    }
    if (mnist->IsImagesLoaded() && mnist->IsLabelsLoaded()) {
        /// Получение данных из базы MNIST]
        unsigned int mnist_count = mnist->ImagesCount();
        /// Резервирование массивов
        float** input_train_values;
        float** output_train_values;
        input_train_values = new float*[mnist_count];
        output_train_values = new float*[mnist_count];
        for (unsigned int i = 0; i < mnist_count; ++i) {
            input_train_values[i] = mnist->GetImage(i)->GetFloatData(0.0f, 1.0f);
            unsigned int label_value = static_cast<unsigned int>(mnist->GetLabel(i));
            /// создание массива выводов
            output_train_values[i] = new float[10];
            for (int j = 0; j < 10; ++j) {
                output_train_values[i][j] = 0.0f;
            }
            output_train_values[i][label_value] = 1.0f;
        }
        train_data_.set_train_data(mnist_count, mnist->Cols() * mnist->Rows(), input_train_values, 10, output_train_values );
        for (unsigned int i = 0; i < mnist_count; ++i) {
            delete[] input_train_values[i];
            delete[] output_train_values[i];
        }
        delete[] input_train_values;
        delete[] output_train_values;
        is_train_loaded_ = true;
    }
    return is_train_loaded_;
}

void ANNRecognizer::Train(unsigned int max_epochs, unsigned int epochs_between_report, float desired_error) {
    if (is_train_loaded_) {
        if (train_data_.num_input_train_data() == net.get_num_input() && train_data_.num_output_train_data() == net.get_num_output())
            net.train_on_data(train_data_, max_epochs, epochs_between_report, desired_error);
        train_data_.destroy_train();
    }
}

bool ANNRecognizer::LoadANN(const std::string config_file) {
    is_ann_init_ = net.create_from_file(config_file);
    return is_ann_init_;
}

void ANNRecognizer::SaveANN(const std::string config_file) {
    net.save(config_file);
}

bool ANNRecognizer::LoadTrain(const std::string train_file) {
    is_train_loaded_ = train_data_.read_train_from_file(train_file);
    return is_train_loaded_;
}

void ANNRecognizer::SaveTrain(const std::string train_file) {
    train_data_.save_train(train_file);
}

bool ANNRecognizer::IsAnnInit() {
    return is_ann_init_;
}

bool ANNRecognizer::IsTrainLoaded() {
    return is_train_loaded_;
}

void ANNRecognizer::CancelTraining() {
    is_train_canceled_ = true;
}

int ANNRecognizer::CallbackFunc(FANN::neural_net& net,
                                FANN::training_data& data,
                                unsigned int max_epochs,
                                unsigned int epochs_between_reports,
                                float desired_error, unsigned int epochs, void*) {
    /*if (is_train_canceled_) {
        is_train_canceled_ = false;
        return -1;
    }*/
    std::cout << "Epochs     " << std::setw(8) << epochs << ". "
         << "Current Error: " << std::left << net.get_MSE() << std::right << std::endl;
    return 0;
}

unsigned char ANNRecognizer::Recognize(ImageData &data) {
    float* img_data = data.GetFloatData(0.0f, 1.0f);
    float* out_array = net.run(img_data);
    unsigned int num_output = net.get_num_output();
    unsigned char out_char = static_cast<unsigned int>(FindMaxItem(out_array, num_output));
    delete[] img_data;
    return out_char;

}

unsigned int ANNRecognizer::FindMaxItem(float *array, unsigned int arr_len) {
    unsigned int index_max = 0;
    for (unsigned int index = 1; index < arr_len; ++index) {
        if (array[index] > array[index_max])
            index_max = index;
    }
    return index_max;
}
