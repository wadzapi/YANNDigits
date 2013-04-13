#include "mnistdataset.h"
#include <cstdio>

MnistDataset::MnistDataset() {

}

unsigned int MnistDataset::Count() const {
    return num_images_;
}



inline void MnistDataset::SwapEndian(int &value) {
   value = (value >> 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value << 24);

}

bool MnistDataset::Load(const char *images_path, const char *labels_path) {
    /// Загружаем массив картинок и массив меток
    bool result = true;
    result = result && LoadLabels(labels_path);
    result = result && LoadImages(images_path);
    return result;

}

bool MnistDataset::LoadLabels(const char *labels_path) {
    FILE* labels_file = fopen(labels_path, "rb");
    if (labels_file == NULL)
        return false;
    fread(&labels_magic_number, sizeof(int), 1, labels_file);
    SwapEndian(labels_magic_number);
    if (labels_magic_number != kMagicTestLabels && labels_magic_number != kMagicTrainLabels) {
        fclose(labels_file);
        return false;
    }
    fread(&num_labels_, sizeof(unsigned char), 1, labels_file);
    SwapEndian(num_labels_);
    int label_counter = 0;
    unsigned char label_value = 0;
    while (!feof(labels_file)) {
        fread((&label_value), sizeof(unsigned char), 1, labels_file);
        mnist_labels.push_back(label_value);
        ++label_counter;
    }
    fclose(labels_file);
    if (label_counter == num_labels_)
        return true;
    else
        return false;
}


bool MnistDataset::LoadImages(const char *images_path) {
    FILE* images_file = fopen(images_path, "rb");
    if (images_file == NULL)
        return false;
    fread(&images_magic_number, sizeof(int), 1, images_file);
    SwapEndian(images_magic_number);
    if (images_magic_number != kMagicTrainImages && images_magic_number != kMagicTestImages) {
        fclose(images_file);
        return false;
    }
    fread(&num_images_, sizeof(int), 1, images_file);
    SwapEndian(num_images_);
    fread(&num_rows_, sizeof(int), 1, images_file);
    SwapEndian(num_rows_);
    fread(&num_cols_, sizeof(int), 1, images_file);
    SwapEndian(num_cols_);
    int pixels_num = num_rows_ * num_cols_;
    unsigned char* image_array = new unsigned char[pixels_num];
    int images_counter = 0;
    ImageData image;
    while (!feof(images_file)) {
        fread(image_array, sizeof(unsigned char), pixels_num, images_file);
        image.Load(image_array, pixels_num);
        mnist_images.push_back(image);
        ++images_counter;
    }
    delete [] image_array;
    fclose(images_file);
    if (images_counter == num_images_)
        return true;
    else
        return false;
}


