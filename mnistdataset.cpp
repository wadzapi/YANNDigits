#include "mnistdataset.h"
#include <cstdio>

MnistDataset::MnistDataset() : dataset_(NULL) {

}

MnistDataset::~MnistDataset() {
    if (dataset_ != NULL) {
        for (int i = 0; i < num_images_; i++) {
            delete dataset_[i];
        }
        delete[] dataset_;
    }
}

void MnistDataset::Load(const char *images_path, const char *labels_path) {
    /// Загружаем массив картинок и массив меток
    images_loaded = LoadImages(images_path);
    if (images_loaded) {
        labels_loaded = LoadLabels(labels_path);
    }
}

bool MnistDataset::LoadLabels(const char *labels_path) {
    FILE* labels_file = fopen(labels_path, "rb");
    if (labels_file == NULL)
        return false;
    fread(&labels_magic_number, sizeof(__int32), 1, labels_file);
    SwapEndian(labels_magic_number);
    if (labels_magic_number != kMagicTestLabels && labels_magic_number != kMagicTrainLabels) {
        fclose(labels_file);
        return false;
    }
    fread(&num_labels_, sizeof(__int32), 1, labels_file);
    SwapEndian(num_labels_);
    labels_ = new unsigned char[num_labels_];
    int labels_read = 0;
    labels_read = fread(labels_, sizeof(unsigned char), num_labels_, labels_file);
    fclose(labels_file);
    if (labels_read == num_labels_)
        return true;
    else
        return false;
}

bool MnistDataset::LoadImages(const char *images_path) {
    FILE* images_file = fopen(images_path, "rb");
    if (images_file == NULL)
        return false;
    /// Чтение информации из заголовка
    fread(&images_magic_number, sizeof(__int32), 1, images_file);
    SwapEndian(images_magic_number);
    if (images_magic_number != kMagicTrainImages && images_magic_number != kMagicTestImages) {
        fclose(images_file);
        return false;
    }
    fread(&num_images_, sizeof(__int32), 1, images_file);
    SwapEndian(num_images_);
    fread(&num_rows_, sizeof(__int32), 1, images_file);
    SwapEndian(num_rows_);
    fread(&num_cols_, sizeof(__int32), 1, images_file);
    SwapEndian(num_cols_);
    /// Инициализация массива данных
    dataset_ = new ImageData*[num_images_];
    int buff_size = num_cols_ * num_rows_;
    unsigned char buffer[buff_size];
    for (int i = 0; i < num_images_; ++i) {
        if (feof(images_file)) {
            fclose(images_file);
            return false;
        }
        fread(buffer, sizeof(unsigned char), buff_size, images_file);
        dataset_[i] = new ImageData(num_cols_, num_rows_);
        dataset_[i]->Load(buffer, buff_size);
    }
    fclose(images_file);
    return true;
}

ImageData *MnistDataset::Get(int index) {
    return dataset_[index];
}

unsigned int MnistDataset::Count() const {
    return num_images_;
}

inline void MnistDataset::SwapEndian(int &value) {
   value = (value >> 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value << 24);
}


