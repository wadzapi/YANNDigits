#include "mnistdataset.h"
#include <cstdio>

MnistDataset::MnistDataset() :
    is_images_loaded(false),
    is_labels_loaded(false),
    images_magic_number(0),
    labels_magic_number(0),
    num_images_(0),
    num_labels_(0),
    num_rows_(0),
    num_cols_(0)
{}

void MnistDataset::DeleteImages() {
    if (is_images_loaded) {
        for (int i = 0; i < num_images_; i++) {
            delete images_[i];
        }
        delete[] images_;
        is_images_loaded = false;
        num_images_ = 0;
        images_magic_number = 0;
    }
}

void MnistDataset::DeleteLabels() {
    if (is_labels_loaded) {
        delete[] labels_;
        is_labels_loaded = false;
        num_labels_ = 0;
        labels_magic_number = 0;
    }
}

MnistDataset::~MnistDataset() {
    DeleteImages();
    DeleteLabels();
}

bool MnistDataset::LoadLabels(const char *labels_path) {
    DeleteLabels();
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
    if (labels_read != num_labels_)
        return false;
    is_labels_loaded = true;
    return true;
}

bool MnistDataset::LoadImages(const char *images_path) {
    DeleteImages();
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
    images_ = new ImageData*[num_images_];
    int buff_size = num_cols_ * num_rows_;
    unsigned char buffer[buff_size];
    for (int i = 0; i < num_images_; ++i) {
        if (feof(images_file)) {
            fclose(images_file);
            return false;
        }
        fread(buffer, sizeof(unsigned char), buff_size, images_file);
        images_[i] = new ImageData(num_cols_, num_rows_);
        images_[i]->Load(buffer, buff_size);
    }
    fclose(images_file);
    is_images_loaded = true;
    return true;
}

ImageData *MnistDataset::GetImage(int index) {
    return images_[index];
}

unsigned char MnistDataset::GetLabel(int index) {
    return labels_[index];
}

int MnistDataset::ImagesCount() const {
    return num_images_;
}

int MnistDataset::LabelsCount() const {
    return num_labels_;
}

bool MnistDataset::IsImagesLoaded() {
    return is_images_loaded;
}

bool MnistDataset::IsLabelsLoaded() {
    return is_labels_loaded;
}

inline void MnistDataset::SwapEndian(int &value) {
   value = (value >> 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value << 24);
}


